library verilog;
use verilog.vl_types.all;
entity altera_mult_add is
    generic(
        extra_latency   : integer := 0;
        dedicated_multiplier_circuitry: string  := "AUTO";
        dsp_block_balancing: string  := "AUTO";
        selected_device_family: string  := "Stratix V";
        lpm_type        : string  := "altmult_add";
        lpm_hint        : string  := "UNUSED";
        width_a         : integer := 1;
        input_register_a0: string  := "CLOCK0";
        input_aclr_a0   : string  := "ACLR0";
        input_source_a0 : string  := "DATAA";
        input_register_a1: string  := "CLOCK0";
        input_aclr_a1   : string  := "ACLR0";
        input_source_a1 : string  := "DATAA";
        input_register_a2: string  := "CLOCK0";
        input_aclr_a2   : string  := "ACLR0";
        input_source_a2 : string  := "DATAA";
        input_register_a3: string  := "CLOCK0";
        input_aclr_a3   : string  := "ACLR0";
        input_source_a3 : string  := "DATAA";
        width_b         : integer := 1;
        input_register_b0: string  := "CLOCK0";
        input_aclr_b0   : string  := "ACLR0";
        input_source_b0 : string  := "DATAB";
        input_register_b1: string  := "CLOCK0";
        input_aclr_b1   : string  := "ACLR0";
        input_source_b1 : string  := "DATAB";
        input_register_b2: string  := "CLOCK0";
        input_aclr_b2   : string  := "ACLR0";
        input_source_b2 : string  := "DATAB";
        input_register_b3: string  := "CLOCK0";
        input_aclr_b3   : string  := "ACLR0";
        input_source_b3 : string  := "DATAB";
        width_c         : integer := 1;
        input_register_c0: string  := "CLOCK0";
        input_aclr_c0   : string  := "ACLR0";
        input_register_c1: string  := "CLOCK0";
        input_aclr_c1   : string  := "ACLR0";
        input_register_c2: string  := "CLOCK0";
        input_aclr_c2   : string  := "ACLR0";
        input_register_c3: string  := "CLOCK0";
        input_aclr_c3   : string  := "ACLR0";
        width_result    : integer := 34;
        output_register : string  := "CLOCK0";
        output_aclr     : string  := "ACLR3";
        port_signa      : string  := "PORT_CONNECTIVITY";
        representation_a: string  := "UNSIGNED";
        signed_register_a: string  := "CLOCK0";
        signed_aclr_a   : string  := "ACLR0";
        signed_pipeline_register_a: string  := "CLOCK0";
        signed_pipeline_aclr_a: string  := "ACLR3";
        port_signb      : string  := "PORT_CONNECTIVITY";
        representation_b: string  := "UNSIGNED";
        signed_register_b: string  := "CLOCK0";
        signed_aclr_b   : string  := "ACLR0";
        signed_pipeline_register_b: string  := "CLOCK0";
        signed_pipeline_aclr_b: string  := "ACLR3";
        number_of_multipliers: integer := 1;
        multiplier1_direction: string  := "UNUSED";
        multiplier3_direction: string  := "UNUSED";
        multiplier_register0: string  := "CLOCK0";
        multiplier_aclr0: string  := "ACLR3";
        multiplier_register1: string  := "CLOCK0";
        multiplier_aclr1: string  := "ACLR3";
        multiplier_register2: string  := "CLOCK0";
        multiplier_aclr2: string  := "ACLR3";
        multiplier_register3: string  := "CLOCK0";
        multiplier_aclr3: string  := "ACLR3";
        port_addnsub1   : string  := "PORT_CONNECTIVITY";
        addnsub_multiplier_register1: string  := "CLOCK0";
        addnsub_multiplier_aclr1: string  := "ACLR3";
        addnsub_multiplier_pipeline_register1: string  := "CLOCK0";
        addnsub_multiplier_pipeline_aclr1: string  := "ACLR3";
        port_addnsub3   : string  := "PORT_CONNECTIVITY";
        addnsub_multiplier_register3: string  := "CLOCK0";
        addnsub_multiplier_aclr3: string  := "ACLR3";
        addnsub_multiplier_pipeline_register3: string  := "CLOCK0";
        addnsub_multiplier_pipeline_aclr3: string  := "ACLR3";
        adder1_rounding : string  := "NO";
        addnsub1_round_register: string  := "CLOCK0";
        addnsub1_round_aclr: string  := "ACLR3";
        addnsub1_round_pipeline_register: string  := "CLOCK0";
        addnsub1_round_pipeline_aclr: string  := "ACLR3";
        adder3_rounding : string  := "NO";
        addnsub3_round_register: string  := "CLOCK0";
        addnsub3_round_aclr: string  := "ACLR3";
        addnsub3_round_pipeline_register: string  := "CLOCK0";
        addnsub3_round_pipeline_aclr: string  := "ACLR3";
        multiplier01_rounding: string  := "NO";
        mult01_round_register: string  := "CLOCK0";
        mult01_round_aclr: string  := "ACLR3";
        multiplier23_rounding: string  := "NO";
        mult23_round_register: string  := "CLOCK0";
        mult23_round_aclr: string  := "ACLR3";
        width_msb       : integer := 17;
        output_rounding : string  := "NO";
        output_round_type: string  := "NEAREST_INTEGER";
        output_round_register: string  := "UNREGISTERED";
        output_round_aclr: string  := "NONE";
        output_round_pipeline_register: string  := "UNREGISTERED";
        output_round_pipeline_aclr: string  := "NONE";
        chainout_rounding: string  := "NO";
        chainout_round_register: string  := "UNREGISTERED";
        chainout_round_aclr: string  := "NONE";
        chainout_round_pipeline_register: string  := "UNREGISTERED";
        chainout_round_pipeline_aclr: string  := "NONE";
        chainout_round_output_register: string  := "UNREGISTERED";
        chainout_round_output_aclr: string  := "NONE";
        multiplier01_saturation: string  := "NO";
        mult01_saturation_register: string  := "CLOCK0";
        mult01_saturation_aclr: string  := "ACLR3";
        multiplier23_saturation: string  := "NO";
        mult23_saturation_register: string  := "CLOCK0";
        mult23_saturation_aclr: string  := "ACLR3";
        port_mult0_is_saturated: string  := "UNUSED";
        port_mult1_is_saturated: string  := "UNUSED";
        port_mult2_is_saturated: string  := "UNUSED";
        port_mult3_is_saturated: string  := "UNUSED";
        width_saturate_sign: integer := 1;
        output_saturation: string  := "NO";
        port_output_is_overflow: string  := "PORT_UNUSED";
        output_saturate_type: string  := "ASYMMETRIC";
        output_saturate_register: string  := "UNREGISTERED";
        output_saturate_aclr: string  := "NONE";
        output_saturate_pipeline_register: string  := "UNREGISTERED";
        output_saturate_pipeline_aclr: string  := "NONE";
        chainout_saturation: string  := "NO";
        port_chainout_sat_is_overflow: string  := "PORT_UNUSED";
        chainout_saturate_register: string  := "UNREGISTERED";
        chainout_saturate_aclr: string  := "NONE";
        chainout_saturate_pipeline_register: string  := "UNREGISTERED";
        chainout_saturate_pipeline_aclr: string  := "NONE";
        chainout_saturate_output_register: string  := "UNREGISTERED";
        chainout_saturate_output_aclr: string  := "NONE";
        scanouta_register: string  := "UNREGISTERED";
        scanouta_aclr   : string  := "NONE";
        width_chainin   : integer := 1;
        chainout_adder  : string  := "NO";
        chainout_register: string  := "UNREGISTERED";
        chainout_aclr   : string  := "ACLR3";
        zero_chainout_output_register: string  := "UNREGISTERED";
        zero_chainout_output_aclr: string  := "NONE";
        shift_mode      : string  := "NO";
        rotate_register : string  := "UNREGISTERED";
        rotate_aclr     : string  := "NONE";
        rotate_pipeline_register: string  := "UNREGISTERED";
        rotate_pipeline_aclr: string  := "NONE";
        rotate_output_register: string  := "UNREGISTERED";
        rotate_output_aclr: string  := "NONE";
        shift_right_register: string  := "UNREGISTERED";
        shift_right_aclr: string  := "NONE";
        shift_right_pipeline_register: string  := "UNREGISTERED";
        shift_right_pipeline_aclr: string  := "NONE";
        shift_right_output_register: string  := "UNREGISTERED";
        shift_right_output_aclr: string  := "NONE";
        zero_loopback_register: string  := "UNREGISTERED";
        zero_loopback_aclr: string  := "NONE";
        zero_loopback_pipeline_register: string  := "UNREGISTERED";
        zero_loopback_pipeline_aclr: string  := "NONE";
        zero_loopback_output_register: string  := "UNREGISTERED";
        zero_loopback_output_aclr: string  := "NONE";
        accumulator     : string  := "NO";
        accum_direction : string  := "ADD";
        loadconst_value : integer := 0;
        use_accum_sload_interchange: string  := "FALSE";
        accum_sload_register: string  := "UNREGISTERED";
        accum_sload_aclr: string  := "NONE";
        accum_sload_pipeline_register: string  := "UNREGISTERED";
        accum_sload_pipeline_aclr: string  := "NONE";
        loadconst_control_register: string  := "CLOCK0";
        loadconst_control_aclr: string  := "ACLR0";
        double_accum    : string  := "NO";
        systolic_delay1 : string  := "UNREGISTERED";
        systolic_delay3 : string  := "UNREGISTERED";
        systolic_aclr1  : string  := "NONE";
        systolic_aclr3  : string  := "NONE";
        preadder_mode   : string  := "SIMPLE";
        preadder_direction_0: string  := "ADD";
        preadder_direction_1: string  := "ADD";
        preadder_direction_2: string  := "ADD";
        preadder_direction_3: string  := "ADD";
        width_coef      : integer := 1;
        coefsel0_register: string  := "CLOCK0";
        coefsel0_aclr   : string  := "ACLR0";
        coefsel1_register: string  := "CLOCK0";
        coefsel1_aclr   : string  := "ACLR0";
        coefsel2_register: string  := "CLOCK0";
        coefsel2_aclr   : string  := "ACLR0";
        coefsel3_register: string  := "CLOCK0";
        coefsel3_aclr   : string  := "ACLR0";
        coef0_0         : integer := 0;
        coef0_1         : integer := 0;
        coef0_2         : integer := 0;
        coef0_3         : integer := 0;
        coef0_4         : integer := 0;
        coef0_5         : integer := 0;
        coef0_6         : integer := 0;
        coef0_7         : integer := 0;
        coef1_0         : integer := 0;
        coef1_1         : integer := 0;
        coef1_2         : integer := 0;
        coef1_3         : integer := 0;
        coef1_4         : integer := 0;
        coef1_5         : integer := 0;
        coef1_6         : integer := 0;
        coef1_7         : integer := 0;
        coef2_0         : integer := 0;
        coef2_1         : integer := 0;
        coef2_2         : integer := 0;
        coef2_3         : integer := 0;
        coef2_4         : integer := 0;
        coef2_5         : integer := 0;
        coef2_6         : integer := 0;
        coef2_7         : integer := 0;
        coef3_0         : integer := 0;
        coef3_1         : integer := 0;
        coef3_2         : integer := 0;
        coef3_3         : integer := 0;
        coef3_4         : integer := 0;
        coef3_5         : integer := 0;
        coef3_6         : integer := 0;
        coef3_7         : integer := 0;
        width_clock_all_wire_msb: integer := 3;
        width_aclr_all_wire_msb: integer := 3;
        width_ena_all_wire_msb: integer := 3;
        width_a_total_msb: vl_notype;
        width_a_msb     : vl_notype;
        width_b_total_msb: vl_notype;
        width_b_msb     : vl_notype;
        width_c_total_msb: vl_notype;
        width_c_msb     : vl_notype;
        width_scanina   : vl_notype;
        width_scanina_msb: vl_notype;
        width_scaninb   : vl_notype;
        width_scaninb_msb: vl_notype;
        width_sourcea_msb: vl_notype;
        width_sourceb_msb: vl_notype;
        width_scanouta_msb: vl_notype;
        width_scanoutb_msb: vl_notype;
        width_chainin_msb: vl_notype;
        width_result_msb: vl_notype;
        width_coef_msb  : vl_notype;
        dataa_split_ext_require: vl_notype;
        dataa_port_sign : vl_notype;
        width_a_ext     : vl_notype;
        width_a_ext_msb : vl_notype;
        datab_split_ext_require: vl_notype;
        datab_port_sign : vl_notype;
        width_b_ext     : vl_notype;
        width_b_ext_msb : vl_notype;
        coef_ext_require: vl_notype;
        coef_port_sign  : vl_notype;
        width_coef_ext  : vl_notype;
        width_coef_ext_msb: vl_notype;
        datac_split_ext_require: vl_notype;
        datac_port_sign : vl_notype;
        width_c_ext     : vl_notype;
        width_c_ext_msb : vl_notype;
        width_scanchain : vl_notype;
        width_scanchain_msb: vl_notype;
        scanchain_port_sign: vl_notype;
        preadder_representation: vl_notype;
        width_preadder_input_a: vl_notype;
        width_preadder_input_a_msb: vl_notype;
        width_preadder_adder_result: vl_notype;
        width_preadder_output_a: vl_notype;
        width_preadder_output_a_msb: vl_notype;
        width_preadder_output_b: vl_notype;
        width_preadder_output_b_msb: vl_notype;
        multiplier_input_representation_a: vl_notype;
        multiplier_input_representation_b: vl_notype;
        width_mult_source_a: vl_notype;
        width_mult_source_a_msb: vl_notype;
        width_mult_source_b: vl_notype;
        width_mult_source_b_msb: vl_notype;
        width_mult_result: vl_notype;
        width_mult_result_msb: vl_notype;
        width_adder_source: vl_notype;
        width_adder_source_msb: vl_notype;
        width_adder_result: vl_notype;
        width_adder_result_msb: vl_notype;
        width_chainin_ext: vl_notype;
        width_original_result: vl_notype;
        width_original_result_msb: vl_notype;
        result_ext_width: vl_notype;
        width_result_output: vl_notype;
        width_result_output_msb: vl_notype;
        width_chainout_adder_output: vl_notype
    );
    port(
        dataa           : in     vl_logic_vector;
        datab           : in     vl_logic_vector;
        datac           : in     vl_logic_vector;
        scanina         : in     vl_logic_vector;
        scaninb         : in     vl_logic_vector;
        sourcea         : in     vl_logic_vector;
        sourceb         : in     vl_logic_vector;
        clock3          : in     vl_logic;
        clock2          : in     vl_logic;
        clock1          : in     vl_logic;
        clock0          : in     vl_logic;
        aclr3           : in     vl_logic;
        aclr2           : in     vl_logic;
        aclr1           : in     vl_logic;
        aclr0           : in     vl_logic;
        ena3            : in     vl_logic;
        ena2            : in     vl_logic;
        ena1            : in     vl_logic;
        ena0            : in     vl_logic;
        signa           : in     vl_logic;
        signb           : in     vl_logic;
        addnsub1        : in     vl_logic;
        addnsub3        : in     vl_logic;
        result          : out    vl_logic_vector;
        scanouta        : out    vl_logic_vector;
        scanoutb        : out    vl_logic_vector;
        mult01_round    : in     vl_logic;
        mult23_round    : in     vl_logic;
        mult01_saturation: in     vl_logic;
        mult23_saturation: in     vl_logic;
        addnsub1_round  : in     vl_logic;
        addnsub3_round  : in     vl_logic;
        mult0_is_saturated: out    vl_logic;
        mult1_is_saturated: out    vl_logic;
        mult2_is_saturated: out    vl_logic;
        mult3_is_saturated: out    vl_logic;
        output_round    : in     vl_logic;
        chainout_round  : in     vl_logic;
        output_saturate : in     vl_logic;
        chainout_saturate: in     vl_logic;
        overflow        : out    vl_logic;
        chainout_sat_overflow: out    vl_logic;
        chainin         : in     vl_logic_vector;
        zero_chainout   : in     vl_logic;
        rotate          : in     vl_logic;
        shift_right     : in     vl_logic;
        zero_loopback   : in     vl_logic;
        accum_sload     : in     vl_logic;
        coefsel0        : in     vl_logic_vector(2 downto 0);
        coefsel1        : in     vl_logic_vector(2 downto 0);
        coefsel2        : in     vl_logic_vector(2 downto 0);
        coefsel3        : in     vl_logic_vector(2 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of extra_latency : constant is 1;
    attribute mti_svvh_generic_type of dedicated_multiplier_circuitry : constant is 1;
    attribute mti_svvh_generic_type of dsp_block_balancing : constant is 1;
    attribute mti_svvh_generic_type of selected_device_family : constant is 1;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of lpm_hint : constant is 1;
    attribute mti_svvh_generic_type of width_a : constant is 1;
    attribute mti_svvh_generic_type of input_register_a0 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_a0 : constant is 1;
    attribute mti_svvh_generic_type of input_source_a0 : constant is 1;
    attribute mti_svvh_generic_type of input_register_a1 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_a1 : constant is 1;
    attribute mti_svvh_generic_type of input_source_a1 : constant is 1;
    attribute mti_svvh_generic_type of input_register_a2 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_a2 : constant is 1;
    attribute mti_svvh_generic_type of input_source_a2 : constant is 1;
    attribute mti_svvh_generic_type of input_register_a3 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_a3 : constant is 1;
    attribute mti_svvh_generic_type of input_source_a3 : constant is 1;
    attribute mti_svvh_generic_type of width_b : constant is 1;
    attribute mti_svvh_generic_type of input_register_b0 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_b0 : constant is 1;
    attribute mti_svvh_generic_type of input_source_b0 : constant is 1;
    attribute mti_svvh_generic_type of input_register_b1 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_b1 : constant is 1;
    attribute mti_svvh_generic_type of input_source_b1 : constant is 1;
    attribute mti_svvh_generic_type of input_register_b2 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_b2 : constant is 1;
    attribute mti_svvh_generic_type of input_source_b2 : constant is 1;
    attribute mti_svvh_generic_type of input_register_b3 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_b3 : constant is 1;
    attribute mti_svvh_generic_type of input_source_b3 : constant is 1;
    attribute mti_svvh_generic_type of width_c : constant is 1;
    attribute mti_svvh_generic_type of input_register_c0 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_c0 : constant is 1;
    attribute mti_svvh_generic_type of input_register_c1 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_c1 : constant is 1;
    attribute mti_svvh_generic_type of input_register_c2 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_c2 : constant is 1;
    attribute mti_svvh_generic_type of input_register_c3 : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_c3 : constant is 1;
    attribute mti_svvh_generic_type of width_result : constant is 1;
    attribute mti_svvh_generic_type of output_register : constant is 1;
    attribute mti_svvh_generic_type of output_aclr : constant is 1;
    attribute mti_svvh_generic_type of port_signa : constant is 1;
    attribute mti_svvh_generic_type of representation_a : constant is 1;
    attribute mti_svvh_generic_type of signed_register_a : constant is 1;
    attribute mti_svvh_generic_type of signed_aclr_a : constant is 1;
    attribute mti_svvh_generic_type of signed_pipeline_register_a : constant is 1;
    attribute mti_svvh_generic_type of signed_pipeline_aclr_a : constant is 1;
    attribute mti_svvh_generic_type of port_signb : constant is 1;
    attribute mti_svvh_generic_type of representation_b : constant is 1;
    attribute mti_svvh_generic_type of signed_register_b : constant is 1;
    attribute mti_svvh_generic_type of signed_aclr_b : constant is 1;
    attribute mti_svvh_generic_type of signed_pipeline_register_b : constant is 1;
    attribute mti_svvh_generic_type of signed_pipeline_aclr_b : constant is 1;
    attribute mti_svvh_generic_type of number_of_multipliers : constant is 1;
    attribute mti_svvh_generic_type of multiplier1_direction : constant is 1;
    attribute mti_svvh_generic_type of multiplier3_direction : constant is 1;
    attribute mti_svvh_generic_type of multiplier_register0 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_aclr0 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_register1 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_aclr1 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_register2 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_aclr2 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_register3 : constant is 1;
    attribute mti_svvh_generic_type of multiplier_aclr3 : constant is 1;
    attribute mti_svvh_generic_type of port_addnsub1 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_register1 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_aclr1 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_pipeline_register1 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_pipeline_aclr1 : constant is 1;
    attribute mti_svvh_generic_type of port_addnsub3 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_register3 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_aclr3 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_pipeline_register3 : constant is 1;
    attribute mti_svvh_generic_type of addnsub_multiplier_pipeline_aclr3 : constant is 1;
    attribute mti_svvh_generic_type of adder1_rounding : constant is 1;
    attribute mti_svvh_generic_type of addnsub1_round_register : constant is 1;
    attribute mti_svvh_generic_type of addnsub1_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of addnsub1_round_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of addnsub1_round_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of adder3_rounding : constant is 1;
    attribute mti_svvh_generic_type of addnsub3_round_register : constant is 1;
    attribute mti_svvh_generic_type of addnsub3_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of addnsub3_round_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of addnsub3_round_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of multiplier01_rounding : constant is 1;
    attribute mti_svvh_generic_type of mult01_round_register : constant is 1;
    attribute mti_svvh_generic_type of mult01_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of multiplier23_rounding : constant is 1;
    attribute mti_svvh_generic_type of mult23_round_register : constant is 1;
    attribute mti_svvh_generic_type of mult23_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of width_msb : constant is 1;
    attribute mti_svvh_generic_type of output_rounding : constant is 1;
    attribute mti_svvh_generic_type of output_round_type : constant is 1;
    attribute mti_svvh_generic_type of output_round_register : constant is 1;
    attribute mti_svvh_generic_type of output_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of output_round_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of output_round_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_rounding : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_output_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_round_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of multiplier01_saturation : constant is 1;
    attribute mti_svvh_generic_type of mult01_saturation_register : constant is 1;
    attribute mti_svvh_generic_type of mult01_saturation_aclr : constant is 1;
    attribute mti_svvh_generic_type of multiplier23_saturation : constant is 1;
    attribute mti_svvh_generic_type of mult23_saturation_register : constant is 1;
    attribute mti_svvh_generic_type of mult23_saturation_aclr : constant is 1;
    attribute mti_svvh_generic_type of port_mult0_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of port_mult1_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of port_mult2_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of port_mult3_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of width_saturate_sign : constant is 1;
    attribute mti_svvh_generic_type of output_saturation : constant is 1;
    attribute mti_svvh_generic_type of port_output_is_overflow : constant is 1;
    attribute mti_svvh_generic_type of output_saturate_type : constant is 1;
    attribute mti_svvh_generic_type of output_saturate_register : constant is 1;
    attribute mti_svvh_generic_type of output_saturate_aclr : constant is 1;
    attribute mti_svvh_generic_type of output_saturate_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of output_saturate_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturation : constant is 1;
    attribute mti_svvh_generic_type of port_chainout_sat_is_overflow : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_output_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_saturate_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of scanouta_register : constant is 1;
    attribute mti_svvh_generic_type of scanouta_aclr : constant is 1;
    attribute mti_svvh_generic_type of width_chainin : constant is 1;
    attribute mti_svvh_generic_type of chainout_adder : constant is 1;
    attribute mti_svvh_generic_type of chainout_register : constant is 1;
    attribute mti_svvh_generic_type of chainout_aclr : constant is 1;
    attribute mti_svvh_generic_type of zero_chainout_output_register : constant is 1;
    attribute mti_svvh_generic_type of zero_chainout_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of shift_mode : constant is 1;
    attribute mti_svvh_generic_type of rotate_register : constant is 1;
    attribute mti_svvh_generic_type of rotate_aclr : constant is 1;
    attribute mti_svvh_generic_type of rotate_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of rotate_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of rotate_output_register : constant is 1;
    attribute mti_svvh_generic_type of rotate_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of shift_right_register : constant is 1;
    attribute mti_svvh_generic_type of shift_right_aclr : constant is 1;
    attribute mti_svvh_generic_type of shift_right_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of shift_right_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of shift_right_output_register : constant is 1;
    attribute mti_svvh_generic_type of shift_right_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_register : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_aclr : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_output_register : constant is 1;
    attribute mti_svvh_generic_type of zero_loopback_output_aclr : constant is 1;
    attribute mti_svvh_generic_type of accumulator : constant is 1;
    attribute mti_svvh_generic_type of accum_direction : constant is 1;
    attribute mti_svvh_generic_type of loadconst_value : constant is 1;
    attribute mti_svvh_generic_type of use_accum_sload_interchange : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_register : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_pipeline_register : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of loadconst_control_register : constant is 1;
    attribute mti_svvh_generic_type of loadconst_control_aclr : constant is 1;
    attribute mti_svvh_generic_type of double_accum : constant is 1;
    attribute mti_svvh_generic_type of systolic_delay1 : constant is 1;
    attribute mti_svvh_generic_type of systolic_delay3 : constant is 1;
    attribute mti_svvh_generic_type of systolic_aclr1 : constant is 1;
    attribute mti_svvh_generic_type of systolic_aclr3 : constant is 1;
    attribute mti_svvh_generic_type of preadder_mode : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_0 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_1 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_2 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_3 : constant is 1;
    attribute mti_svvh_generic_type of width_coef : constant is 1;
    attribute mti_svvh_generic_type of coefsel0_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel0_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel1_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel1_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel2_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel2_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel3_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel3_aclr : constant is 1;
    attribute mti_svvh_generic_type of coef0_0 : constant is 1;
    attribute mti_svvh_generic_type of coef0_1 : constant is 1;
    attribute mti_svvh_generic_type of coef0_2 : constant is 1;
    attribute mti_svvh_generic_type of coef0_3 : constant is 1;
    attribute mti_svvh_generic_type of coef0_4 : constant is 1;
    attribute mti_svvh_generic_type of coef0_5 : constant is 1;
    attribute mti_svvh_generic_type of coef0_6 : constant is 1;
    attribute mti_svvh_generic_type of coef0_7 : constant is 1;
    attribute mti_svvh_generic_type of coef1_0 : constant is 1;
    attribute mti_svvh_generic_type of coef1_1 : constant is 1;
    attribute mti_svvh_generic_type of coef1_2 : constant is 1;
    attribute mti_svvh_generic_type of coef1_3 : constant is 1;
    attribute mti_svvh_generic_type of coef1_4 : constant is 1;
    attribute mti_svvh_generic_type of coef1_5 : constant is 1;
    attribute mti_svvh_generic_type of coef1_6 : constant is 1;
    attribute mti_svvh_generic_type of coef1_7 : constant is 1;
    attribute mti_svvh_generic_type of coef2_0 : constant is 1;
    attribute mti_svvh_generic_type of coef2_1 : constant is 1;
    attribute mti_svvh_generic_type of coef2_2 : constant is 1;
    attribute mti_svvh_generic_type of coef2_3 : constant is 1;
    attribute mti_svvh_generic_type of coef2_4 : constant is 1;
    attribute mti_svvh_generic_type of coef2_5 : constant is 1;
    attribute mti_svvh_generic_type of coef2_6 : constant is 1;
    attribute mti_svvh_generic_type of coef2_7 : constant is 1;
    attribute mti_svvh_generic_type of coef3_0 : constant is 1;
    attribute mti_svvh_generic_type of coef3_1 : constant is 1;
    attribute mti_svvh_generic_type of coef3_2 : constant is 1;
    attribute mti_svvh_generic_type of coef3_3 : constant is 1;
    attribute mti_svvh_generic_type of coef3_4 : constant is 1;
    attribute mti_svvh_generic_type of coef3_5 : constant is 1;
    attribute mti_svvh_generic_type of coef3_6 : constant is 1;
    attribute mti_svvh_generic_type of coef3_7 : constant is 1;
    attribute mti_svvh_generic_type of width_clock_all_wire_msb : constant is 1;
    attribute mti_svvh_generic_type of width_aclr_all_wire_msb : constant is 1;
    attribute mti_svvh_generic_type of width_ena_all_wire_msb : constant is 1;
    attribute mti_svvh_generic_type of width_a_total_msb : constant is 3;
    attribute mti_svvh_generic_type of width_a_msb : constant is 3;
    attribute mti_svvh_generic_type of width_b_total_msb : constant is 3;
    attribute mti_svvh_generic_type of width_b_msb : constant is 3;
    attribute mti_svvh_generic_type of width_c_total_msb : constant is 3;
    attribute mti_svvh_generic_type of width_c_msb : constant is 3;
    attribute mti_svvh_generic_type of width_scanina : constant is 3;
    attribute mti_svvh_generic_type of width_scanina_msb : constant is 3;
    attribute mti_svvh_generic_type of width_scaninb : constant is 3;
    attribute mti_svvh_generic_type of width_scaninb_msb : constant is 3;
    attribute mti_svvh_generic_type of width_sourcea_msb : constant is 3;
    attribute mti_svvh_generic_type of width_sourceb_msb : constant is 3;
    attribute mti_svvh_generic_type of width_scanouta_msb : constant is 3;
    attribute mti_svvh_generic_type of width_scanoutb_msb : constant is 3;
    attribute mti_svvh_generic_type of width_chainin_msb : constant is 3;
    attribute mti_svvh_generic_type of width_result_msb : constant is 3;
    attribute mti_svvh_generic_type of width_coef_msb : constant is 3;
    attribute mti_svvh_generic_type of dataa_split_ext_require : constant is 3;
    attribute mti_svvh_generic_type of dataa_port_sign : constant is 3;
    attribute mti_svvh_generic_type of width_a_ext : constant is 3;
    attribute mti_svvh_generic_type of width_a_ext_msb : constant is 3;
    attribute mti_svvh_generic_type of datab_split_ext_require : constant is 3;
    attribute mti_svvh_generic_type of datab_port_sign : constant is 3;
    attribute mti_svvh_generic_type of width_b_ext : constant is 3;
    attribute mti_svvh_generic_type of width_b_ext_msb : constant is 3;
    attribute mti_svvh_generic_type of coef_ext_require : constant is 3;
    attribute mti_svvh_generic_type of coef_port_sign : constant is 3;
    attribute mti_svvh_generic_type of width_coef_ext : constant is 3;
    attribute mti_svvh_generic_type of width_coef_ext_msb : constant is 3;
    attribute mti_svvh_generic_type of datac_split_ext_require : constant is 3;
    attribute mti_svvh_generic_type of datac_port_sign : constant is 3;
    attribute mti_svvh_generic_type of width_c_ext : constant is 3;
    attribute mti_svvh_generic_type of width_c_ext_msb : constant is 3;
    attribute mti_svvh_generic_type of width_scanchain : constant is 3;
    attribute mti_svvh_generic_type of width_scanchain_msb : constant is 3;
    attribute mti_svvh_generic_type of scanchain_port_sign : constant is 3;
    attribute mti_svvh_generic_type of preadder_representation : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_input_a : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_input_a_msb : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_adder_result : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_output_a : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_output_a_msb : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_output_b : constant is 3;
    attribute mti_svvh_generic_type of width_preadder_output_b_msb : constant is 3;
    attribute mti_svvh_generic_type of multiplier_input_representation_a : constant is 3;
    attribute mti_svvh_generic_type of multiplier_input_representation_b : constant is 3;
    attribute mti_svvh_generic_type of width_mult_source_a : constant is 3;
    attribute mti_svvh_generic_type of width_mult_source_a_msb : constant is 3;
    attribute mti_svvh_generic_type of width_mult_source_b : constant is 3;
    attribute mti_svvh_generic_type of width_mult_source_b_msb : constant is 3;
    attribute mti_svvh_generic_type of width_mult_result : constant is 3;
    attribute mti_svvh_generic_type of width_mult_result_msb : constant is 3;
    attribute mti_svvh_generic_type of width_adder_source : constant is 3;
    attribute mti_svvh_generic_type of width_adder_source_msb : constant is 3;
    attribute mti_svvh_generic_type of width_adder_result : constant is 3;
    attribute mti_svvh_generic_type of width_adder_result_msb : constant is 3;
    attribute mti_svvh_generic_type of width_chainin_ext : constant is 3;
    attribute mti_svvh_generic_type of width_original_result : constant is 3;
    attribute mti_svvh_generic_type of width_original_result_msb : constant is 3;
    attribute mti_svvh_generic_type of result_ext_width : constant is 3;
    attribute mti_svvh_generic_type of width_result_output : constant is 3;
    attribute mti_svvh_generic_type of width_result_output_msb : constant is 3;
    attribute mti_svvh_generic_type of width_chainout_adder_output : constant is 3;
end altera_mult_add;
