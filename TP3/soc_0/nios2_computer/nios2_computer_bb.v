
module nios2_computer (
	clk_clk,
	reset_reset_n,
	leds_external_connection_export,
	switches_external_connection_export,
	key1_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	leds_external_connection_export;
	input	[7:0]	switches_external_connection_export;
	input		key1_external_connection_export;
endmodule
