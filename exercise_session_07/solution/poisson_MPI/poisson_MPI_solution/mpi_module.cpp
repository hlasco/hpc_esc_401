#include <mpi.h>
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, params *p){

	if (p->domain_decomposition==1){
        // Number of process in each dimension
        p->nproc_x = size;
        p->nproc_y = 1;

		p->ymin = 0;
		p->ymax = ny; //will go up to max_y-1

		p->xmin = nx/size*my_rank;
		if (my_rank == size -1)
			p->xmax = nx;
		else 
			p->xmax = nx/size*(my_rank+1);

        // Store ranks of neighbors
        p->right_rank = (my_rank + 1);
        if (p->right_rank >= size) p->right_rank = -1;
        p->left_rank = (my_rank - 1);
        p->top_rank=-1;
        p->bottom_rank=-1;

        // Group for synchronous split communication
        if (my_rank%2==0)
            p->my_group=1;
        else
            p->my_group=2;

        // Store communicator
        p->comm = MPI_COMM_WORLD;
	}

	else if (p->domain_decomposition==2){
        // Number of process in each dimension
        p->nproc_x = size;
        p->nproc_y = 1;

		p->ymin = 0;
		p->ymax = ny; //will go up to max_y-1

		if (my_rank < nx%size){
			p->xmin = (nx/size+1)*my_rank;
			p->xmax = (nx/size+1)*(my_rank+1);	
		}
		else{
			p->xmin = nx/size*my_rank + nx%size;
			p->xmax = nx/size*(my_rank+1) + nx%size;		
		}

        // Store ranks of neighbors
        p->right_rank = (my_rank + 1);
        if (p->right_rank >= size) p->right_rank = -1;
        p->left_rank = (my_rank - 1);
        p->top_rank=-1;
        p->bottom_rank=-1;

        // Group for synchronous split communication
        if (my_rank%2==0)
            p->my_group=1;
        else
            p->my_group=2;

        // Store communicator
        p->comm = MPI_COMM_WORLD;
	}

	else if (p->domain_decomposition==3){
        int indices[2];
        int dims[2] = {0, 0};

        // Compute number of process in each dimension
        MPI_Dims_create(size, 2, dims);
        p->nproc_x = dims[0];
        p->nproc_y = dims[1];

        // Create Cartesian communicator
        MPI_Comm comm_cartesian;
        int periods[2]={0,0};
        MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &comm_cartesian);
        p->comm = comm_cartesian;
    
        // Compute new rank
        MPI_Comm_rank(p->comm,&my_rank);

        // Compute coordinate on the grid
        MPI_Cart_coords(p->comm,my_rank,2,indices);
    
        // Compute neighbor ranks
        MPI_Cart_shift(p->comm, 0, 1, &p->left_rank, &p->right_rank);
        MPI_Cart_shift(p->comm, 1, 1, &p->bottom_rank, &p->top_rank);

        // Group for synchronous split communication
        if (indices[0]%2==indices[1]%2)
            p->my_group = 1;
        else
            p->my_group = 2;

        printf("%d, %d, my_group=%d\n",indices[0], indices[1], p->my_group);
    
        // Compute local domain corners
        if (indices[0] < p->nx%p->nproc_x){
            p->xmin = (p->nx/p->nproc_x+1)*indices[0];
            p->xmax = (p->nx/p->nproc_x+1)*(indices[0]+1);  
        }
        else{
            p->xmin = p->nx/p->nproc_x*indices[0] + p->nx%p->nproc_x;
            p->xmax = p->nx/p->nproc_x*(indices[0]+1) + p->nx%p->nproc_x;       
        }
    
        if (indices[1] < p->ny%p->nproc_y){
            p->ymin = (p->ny/p->nproc_y+1)*indices[1];
            p->ymax = (p->ny/p->nproc_y+1)*(indices[1]+1);  
        }
        else{
            p->ymin = p->ny/p->nproc_y*indices[1] + p->ny%p->nproc_y;
            p->ymax = p->ny/p->nproc_y*(indices[1]+1) + p->ny%p->nproc_y;       
        }

	}
	else printf("Domain decomposision %d not implemented\n", p->domain_decomposition);

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,p->xmin,p->xmax,p->ymin,p->ymax);
    printf("I am rank %d, my neighbours are: left: %d, right: %d, bottom: %d, top: %d\n",my_rank,p->left_rank, p->right_rank, p->bottom_rank, p->top_rank);
	return 0;
}

void halo_comm(params p, int my_rank, int size, double** u, 
               double* fromLeft, double* fromRight, double* fromTop, double* fromBottom, 
               MPI_Request* requests){

    int size_x = p.xmax-p.xmin;
    int size_y = p.ymax-p.ymin;

    double col_to_right[size_y], col_to_left[size_y];
	for (int j=0;j<size_y;j++) col_to_right[j] = u[size_x - 1][j];
	for (int j=0;j<size_y;j++) col_to_left[j] = u[0][j];

    double row_to_top[size_y], row_to_bottom[size_x];
    if (p.domain_decomposition==3){
        for (int j=0;j<size_x;j++) row_to_top[j] = u[j][size_y - 1]; 
        for (int j=0;j<size_x;j++) row_to_bottom[j] = u[j][0];
    }

    // Blocking communication strategy
    if (p.communication==1){
    	if (p.my_group==1){
    		if (p.right_rank>=0) MPI_Send(col_to_right, size_y, MPI_DOUBLE, p.right_rank, 0, p.comm);
    		if (p.left_rank>=0)  MPI_Send(col_to_left,  size_y, MPI_DOUBLE, p.left_rank,  0, p.comm);
			if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, p.comm, MPI_STATUS_IGNORE); 
			if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, p.comm, MPI_STATUS_IGNORE);
            if (p.domain_decomposition==3){
                if (p.top_rank>=0)    MPI_Send(row_to_top,    size_x, MPI_DOUBLE, p.top_rank,    0, p.comm);
                if (p.bottom_rank>=0) MPI_Send(row_to_bottom, size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm);
                if (p.top_rank>=0)    MPI_Recv(fromTop,       size_x, MPI_DOUBLE, p.top_rank,    0, p.comm, MPI_STATUS_IGNORE); 
                if (p.bottom_rank>=0) MPI_Recv(fromBottom,    size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm, MPI_STATUS_IGNORE);
            }
    	}
    	else{
			if (p.left_rank>=0)  MPI_Recv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, p.comm, MPI_STATUS_IGNORE);
			if (p.right_rank>=0) MPI_Recv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, p.comm, MPI_STATUS_IGNORE);
			if (p.left_rank>=0)  MPI_Send(col_to_left,  size_y, MPI_DOUBLE, p.left_rank,  0, p.comm);		
			if (p.right_rank>=0) MPI_Send(col_to_right, size_y, MPI_DOUBLE, p.right_rank, 0, p.comm);
            if (p.domain_decomposition==3){
                if (p.top_rank>=0)    MPI_Recv(fromTop,       size_x, MPI_DOUBLE, p.top_rank,    0, p.comm, MPI_STATUS_IGNORE); 
                if (p.bottom_rank>=0) MPI_Recv(fromBottom,    size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm, MPI_STATUS_IGNORE);  
                if (p.top_rank>=0)    MPI_Send(row_to_top,    size_x, MPI_DOUBLE, p.top_rank,    0, p.comm);
                if (p.bottom_rank>=0) MPI_Send(row_to_bottom, size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm);
            }	
    	}
    }

    // Non-blocking communication strategy
    else{
		if (p.right_rank>=0) MPI_Isend(col_to_right, size_y, MPI_DOUBLE, p.right_rank, 0, p.comm, &requests[0]);
        if (p.left_rank>=0)  MPI_Isend(col_to_left,  size_y, MPI_DOUBLE, p.left_rank,  0, p.comm, &requests[1]);
		if (p.left_rank>=0)  MPI_Irecv(fromLeft,     size_y, MPI_DOUBLE, p.left_rank,  0, p.comm, &requests[2]);
    	if (p.right_rank>=0) MPI_Irecv(fromRight,    size_y, MPI_DOUBLE, p.right_rank, 0, p.comm, &requests[3]);
        if (p.domain_decomposition==3){
            if (p.top_rank>=0)    MPI_Isend(row_to_top,    size_x, MPI_DOUBLE, p.top_rank,    0, p.comm, &requests[4]);
            if (p.bottom_rank>=0) MPI_Isend(row_to_bottom, size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm, &requests[5]);
            if (p.top_rank>=0)    MPI_Irecv(fromTop,       size_x, MPI_DOUBLE, p.top_rank,    0, p.comm, &requests[6]);
            if (p.bottom_rank>=0) MPI_Irecv(fromBottom,    size_x, MPI_DOUBLE, p.bottom_rank, 0, p.comm, &requests[7]);          
        }		
    }

    if (p.communication==2)
        MPI_Waitall(8,requests,MPI_STATUS_IGNORE);
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff, MPI_Comm comm){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, comm);
	return 0;

	}
int BARRIER(MPI_Comm comm){
	MPI_Barrier(comm);
	return 0;
}
