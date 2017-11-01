onerror {exit -code 1}
vlib work
vlog -work work Project.vo
vlog -work work tx.vwf.vt
vsim -novopt -c -t 1ps -L cycloneive_ver -L altera_ver -L altera_mf_ver -L 220model_ver -L sgate_ver -L altera_lnsim_ver work.Interface_bsp_vlg_vec_tst -voptargs="+acc"
vcd file -direction Project.msim.vcd
vcd add -internal Interface_bsp_vlg_vec_tst/*
vcd add -internal Interface_bsp_vlg_vec_tst/i1/*
run -all
quit -f
