module xor_led(
   output wire redled,    // LED to indicate XOR output
      output wire greenled,  // Not used here, can be left floati    ng                                                              11     output wire blueled    // Not used here, can be left floati    ng                                                              12 );                                                              13     wire clk;                                                   14     reg[1:0] inputs;       // Two-bit register to represent A a    nd B
      reg led;               // Register to hold XOR result (LED     output)
      reg[26:0] delay;       // Counter for delay (simulate blink    ing)
 
      // Clock setup
      qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
          .Sys_Clk0(clk)
      );
 
      // Truth table of XOR:
      // A | B | A^B
      // 0 | 0 |  0
      // 0 | 1 |  1
      // 1 | 0 |  1
      // 1 | 1 |  0
  
always @(posedge clk) begin
          delay = delay + 1; // Increment the counter
          if (delay > 20000000) begin // Delay for LED blinking
              delay = 27'b0;                            
            inputs = inputs + 1; // Cycle through all combinati    ons of A and B
          end
 
          // Calculate XOR operation for inputs[0] (A) and inputs    [1] (B)
          led = inputs[0] ^ inputs[1];
      end
 
       assign redled = led;   // XOR output displayed on red LED   
  assign blueled = 1'b0; // Blue LED remains off              
  assign greenled = 1'b0; // Green LED remains off            44 endmodule
  // End of the module
