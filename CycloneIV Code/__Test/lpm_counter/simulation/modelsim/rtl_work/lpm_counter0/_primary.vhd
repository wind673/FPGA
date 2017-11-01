library verilog;
use verilog.vl_types.all;
entity lpm_counter0 is
    port(
        clock           : in     vl_logic;
        updown          : in     vl_logic;
        q               : out    vl_logic_vector(3 downto 0)
    );
end lpm_counter0;
