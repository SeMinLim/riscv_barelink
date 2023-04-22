.DEFAULT_GOAL := all
RISCV_DIR=/mnt/sdb/semin/riscv-gnu-toolchain/build/bin

RISCV_TARGET=$(RISCV_DIR)/riscv64-unknown-linux-gnu-

CFLAGS=-mcmodel=medany -nostdlib -nostartfiles -march=rv32im -mabi=ilp32 -mstrict-align -static -fvisibility=hidden
LDFLAGS=-march=rv32im -nostdlib -nostartfiles -Wl,-T./bare-link.ld
OBJDUMPFLAGS=-d -Mno-aliases
OBJDIR=./obj/


all:
	mkdir -p $(OBJDIR)
	$(RISCV_TARGET)gcc $(CFLAGS) $(LDFLAGS) entry.s minisudoku.c -o $(OBJDIR)/binary.elf
	$(RISCV_TARGET)objdump $(OBJDUMPFLAGS) ./$(OBJDIR)/binary.elf > ./$(OBJDIR)/minisudoku.dump
	cd $(OBJDIR); bash ../strip.sh
	mv $(OBJDIR)/binary.bin $(OBJDIR)/minisudoku.bin
	rm $(OBJDIR)/binary.elf
