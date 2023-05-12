MEMORY
{
    ram (rwx) : ORIGIN = 0x00000000, LENGTH = 0xffffffff /* 4GB */
}
SECTIONS
{
    . = 0x0;
    .text : {
        *(.text)
    } > ram
    .data : ALIGN(0x4000) {
	*(.data)
    } > ram
    .srodata : {
        *(.srodata)
    } > ram
    .riscv.attributes : {
	*(.riscv.attributes)
    } > ram
}
