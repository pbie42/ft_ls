time_t // This is the last access time for the file


mode_t // Specifies the mode of the file. This includes file type information and the file permission bits


nlink_t // The number of hard links to the file. This count keeps track of how many
// directories have entries for this file. If the count is ever decremented
// to zero, then the file itself is discarded as soon as no process still
// holds it open. Symbolic links are not counted in the total.

uid_t // The user ID of the file’s owner

gid_t // The group ID of the file

off_t // This specifies the size of a regular file in bytes. For files that are
// really devices this field isn’t usually meaningful. For symbolic links this
// specifies the length of the file name the link refers to.

ino_t // This is an unsigned integer type used to represent file serial numbers.

blkcnt_t // This is a signed integer type used to represent block counts.

DIR // Represents a directory stream. You shouldn’t ever allocate objects of the
// struct dirent or DIR data types, since the directory access functions do that
// for you. Instead, you refer to these objects using the pointers returned by the it's functions.

dirent // This is a structure type used to return information about directory entries