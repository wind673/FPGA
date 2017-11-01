-- Copyright (C) 1991-2012 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 12.1 Build 177 11/07/2012 SJ Full Version"

-- DATE "09/13/2016 11:57:31"

-- 
-- Device: Altera EP4CGX15BF14C6 Package FBGA169
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIV;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIV.CYCLONEIV_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	counter IS
    PORT (
	pin_out : OUT std_logic_vector(3 DOWNTO 0);
	pin_updown : IN std_logic;
	pin_clock : IN std_logic
	);
END counter;

-- Design Ports Information
-- pin_out[3]	=>  Location: PIN_N10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- pin_out[2]	=>  Location: PIN_L9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- pin_out[1]	=>  Location: PIN_M11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- pin_out[0]	=>  Location: PIN_M9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- pin_clock	=>  Location: PIN_J7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- pin_updown	=>  Location: PIN_N11,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF counter IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_pin_out : std_logic_vector(3 DOWNTO 0);
SIGNAL ww_pin_updown : std_logic;
SIGNAL ww_pin_clock : std_logic;
SIGNAL \pin_clock~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \pin_out[3]~output_o\ : std_logic;
SIGNAL \pin_out[2]~output_o\ : std_logic;
SIGNAL \pin_out[1]~output_o\ : std_logic;
SIGNAL \pin_out[0]~output_o\ : std_logic;
SIGNAL \pin_clock~input_o\ : std_logic;
SIGNAL \pin_clock~inputclkctrl_outclk\ : std_logic;
SIGNAL \pin_updown~input_o\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~combout\ : std_logic;
SIGNAL \~GND~combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~combout\ : std_logic;
SIGNAL \pin_updown~_wirecell_combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~COUT\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0_combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|cout_actual~0_combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~combout\ : std_logic;
SIGNAL \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\ : std_logic_vector(3 DOWNTO 0);

BEGIN

pin_out <= ww_pin_out;
ww_pin_updown <= pin_updown;
ww_pin_clock <= pin_clock;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\pin_clock~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \pin_clock~input_o\);

-- Location: IOOBUF_X26_Y0_N9
\pin_out[3]~output\ : cycloneiv_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3),
	devoe => ww_devoe,
	o => \pin_out[3]~output_o\);

-- Location: IOOBUF_X24_Y0_N9
\pin_out[2]~output\ : cycloneiv_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2),
	devoe => ww_devoe,
	o => \pin_out[2]~output_o\);

-- Location: IOOBUF_X29_Y0_N9
\pin_out[1]~output\ : cycloneiv_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1),
	devoe => ww_devoe,
	o => \pin_out[1]~output_o\);

-- Location: IOOBUF_X24_Y0_N2
\pin_out[0]~output\ : cycloneiv_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0),
	devoe => ww_devoe,
	o => \pin_out[0]~output_o\);

-- Location: IOIBUF_X16_Y0_N15
\pin_clock~input\ : cycloneiv_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_pin_clock,
	o => \pin_clock~input_o\);

-- Location: CLKCTRL_G17
\pin_clock~inputclkctrl\ : cycloneiv_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \pin_clock~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \pin_clock~inputclkctrl_outclk\);

-- Location: IOIBUF_X26_Y0_N1
\pin_updown~input\ : cycloneiv_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_pin_updown,
	o => \pin_updown~input_o\);

-- Location: LCCOMB_X26_Y1_N6
\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~combout\ = \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0) $ (((VCC) # (!\pin_updown~input_o\)))
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\ = CARRY(\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0) $ (!\pin_updown~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110011001",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0),
	datab => \pin_updown~input_o\,
	datad => VCC,
	combout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~combout\,
	cout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\);

-- Location: LCCOMB_X26_Y1_N8
\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~combout\ = (\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1) $ (((\pin_updown~input_o\) # (VCC))))) # 
-- (!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\ & (((\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1)) # (GND))))
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\ = CARRY((\pin_updown~input_o\ $ (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1))) # (!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110001101111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \pin_updown~input_o\,
	datab => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1),
	datad => VCC,
	cin => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~COUT\,
	combout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~combout\,
	cout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\);

-- Location: LCCOMB_X26_Y1_N20
\~GND\ : cycloneiv_lcell_comb
-- Equation(s):
-- \~GND~combout\ = GND

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	combout => \~GND~combout\);

-- Location: LCCOMB_X26_Y1_N4
\pin_updown~_wirecell\ : cycloneiv_lcell_comb
-- Equation(s):
-- \pin_updown~_wirecell_combout\ = !\pin_updown~input_o\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000011111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datad => \pin_updown~input_o\,
	combout => \pin_updown~_wirecell_combout\);

-- Location: FF_X26_Y1_N7
\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \pin_clock~inputclkctrl_outclk\,
	d => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita0~combout\,
	asdata => \pin_updown~_wirecell_combout\,
	sload => \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0));

-- Location: LCCOMB_X26_Y1_N12
\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~combout\ = (\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3) $ (((\pin_updown~input_o\) # (VCC))))) # 
-- (!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\ & ((\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3)) # ((GND))))
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~COUT\ = CARRY((\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3) $ (\pin_updown~input_o\)) # (!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001101111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3),
	datab => \pin_updown~input_o\,
	datad => VCC,
	cin => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\,
	combout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~combout\,
	cout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~COUT\);

-- Location: LCCOMB_X26_Y1_N14
\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0_combout\ = !\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~COUT\

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100001111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	cin => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~COUT\,
	combout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0_combout\);

-- Location: LCCOMB_X26_Y1_N10
\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~combout\ = (\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2) & ((VCC)))) # 
-- (!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2) $ (((VCC) # (!\pin_updown~input_o\)))))
-- \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\ = CARRY((!\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2) $ (!\pin_updown~input_o\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001001",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2),
	datab => \pin_updown~input_o\,
	datad => VCC,
	cin => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~COUT\,
	combout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~combout\,
	cout => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~COUT\);

-- Location: FF_X26_Y1_N11
\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \pin_clock~inputclkctrl_outclk\,
	d => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita2~combout\,
	asdata => \~GND~combout\,
	sload => \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2));

-- Location: LCCOMB_X26_Y1_N0
\inst|LPM_COUNTER_component|auto_generated|cout_actual~0\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|cout_actual~0_combout\ = (\pin_updown~input_o\ & (\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3) & (!\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2) & 
-- !\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000001000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \pin_updown~input_o\,
	datab => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3),
	datac => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(2),
	datad => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1),
	combout => \inst|LPM_COUNTER_component|auto_generated|cout_actual~0_combout\);

-- Location: LCCOMB_X26_Y1_N2
\inst|LPM_COUNTER_component|auto_generated|cout_actual\ : cycloneiv_lcell_comb
-- Equation(s):
-- \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\ = (\inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0_combout\) # ((\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0) & 
-- \inst|LPM_COUNTER_component|auto_generated|cout_actual~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(0),
	datac => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~0_combout\,
	datad => \inst|LPM_COUNTER_component|auto_generated|cout_actual~0_combout\,
	combout => \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\);

-- Location: FF_X26_Y1_N9
\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \pin_clock~inputclkctrl_outclk\,
	d => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita1~combout\,
	asdata => \~GND~combout\,
	sload => \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(1));

-- Location: FF_X26_Y1_N13
\inst|LPM_COUNTER_component|auto_generated|counter_reg_bit[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \pin_clock~inputclkctrl_outclk\,
	d => \inst|LPM_COUNTER_component|auto_generated|counter_comb_bita3~combout\,
	asdata => \pin_updown~_wirecell_combout\,
	sload => \inst|LPM_COUNTER_component|auto_generated|cout_actual~combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \inst|LPM_COUNTER_component|auto_generated|counter_reg_bit\(3));

ww_pin_out(3) <= \pin_out[3]~output_o\;

ww_pin_out(2) <= \pin_out[2]~output_o\;

ww_pin_out(1) <= \pin_out[1]~output_o\;

ww_pin_out(0) <= \pin_out[0]~output_o\;
END structure;


