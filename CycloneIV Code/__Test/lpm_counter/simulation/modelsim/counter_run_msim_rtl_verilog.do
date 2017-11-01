transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+E:/_13_EnglishPath/_01_AX515_Code/__Test/lpm_counter {E:/_13_EnglishPath/_01_AX515_Code/__Test/lpm_counter/lpm_counter0.v}

