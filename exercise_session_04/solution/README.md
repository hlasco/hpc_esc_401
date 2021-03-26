# Exercise session 04

## Exercise 01

**Permissions:**

Default permission of `$HOME`: `rwx------`, which means only the owner read, write and execute permissions.

Default permission of `$SCRATCH`: `rwxr-xr-x`, which means the owner has full access, 
group members have read and execute permissions, non-group members have read and execute permissions.

New files created in these both directories have `rw-r--r--` permission.

The permission in my `$HOME` directory is `rwxr-x---`, which means only me and members of the `uzh4` group could read files there.

**What command can you use to set the access permissions for a directory so only the owner has (full) access?**

You can use `chmod 700 <directory>`

**Create a text file in `$SCRATCH` and set the permissions so that group members can write to it.**

After creating the file, you can add writing permission the group members with `chmod g+w <filename>`

**Create a file and set its permissions to 000. Can you do anything with it now? Is the file completely lost?**

Hopefully the file is not lost after setting permission to `000`. Even though no user can read, write or execute the file, 
the owner still can change the permissions and recover the file.

## Exercise 02 and 03

An exemple of such scripts are in the respective folders.
