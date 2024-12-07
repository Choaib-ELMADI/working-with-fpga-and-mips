	component nios2_computer is
		port (
			clk_clk                             : in  std_logic                    := 'X';             -- clk
			reset_reset_n                       : in  std_logic                    := 'X';             -- reset_n
			leds_external_connection_export     : out std_logic_vector(7 downto 0);                    -- export
			switches_external_connection_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			key1_external_connection_export     : in  std_logic                    := 'X'              -- export
		);
	end component nios2_computer;

	u0 : component nios2_computer
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			leds_external_connection_export     => CONNECTED_TO_leds_external_connection_export,     --     leds_external_connection.export
			switches_external_connection_export => CONNECTED_TO_switches_external_connection_export, -- switches_external_connection.export
			key1_external_connection_export     => CONNECTED_TO_key1_external_connection_export      --     key1_external_connection.export
		);

