LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY soc_0 IS

PORT (
	-- Inputs
	CLOCK_50: IN STD_LOGIC;
	KEY     : IN STD_LOGIC_VECTOR (1 DOWNTO 0);

	SW	    : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
	
	-- Outputs

	LEDR: OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
	HEX0: OUT STD_LOGIC_VECTOR (6 DOWNTO 0);
	HEX1: OUT STD_LOGIC_VECTOR (6 DOWNTO 0);
	HEX2: OUT STD_LOGIC_VECTOR (6 DOWNTO 0);
	HEX3: OUT STD_LOGIC_VECTOR (6 DOWNTO 0)
	);
END soc_0;


ARCHITECTURE nios_computer_rtl OF soc_0 IS

component nios2_computer is
        port (
            clk_clk                             : in  std_logic                    := 'X';             -- clk
            reset_reset_n                       : in  std_logic                    := 'X';             -- reset_n
            leds_external_connection_export     : out std_logic_vector(7 downto 0);                    -- export
            switches_external_connection_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
            key1_external_connection_export     : in  std_logic                    := 'X'              -- export
        );
    end component nios2_computer;
	 
	 begin

    u0 : component nios2_computer
        port map (
            clk_clk                             => clock_50,                             --                          clk.clk
            reset_reset_n                       => key(0),                       --                        reset.reset_n
            leds_external_connection_export     => ledr(7 downto 0),     --     leds_external_connection.export
            switches_external_connection_export => SW(7 downto 0) , -- switches_external_connection.export
            key1_external_connection_export     => key(1)      --     key1_external_connection.export
        );

END nios_computer_rtl;

