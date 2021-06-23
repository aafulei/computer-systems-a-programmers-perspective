/* ---- Homework Problem 11.9 (**) --------------------------------------------
 * Modify Tiny so that when it serves static content, it copies the requested
 * file to the connected descriptor using malloc, rio_readn, and rio_writen,
 * instead of mmap and rio_writen.
 * ------------------------------------------------------------------------- */
