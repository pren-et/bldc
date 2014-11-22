----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:45:53 11/22/2014 
-- Design Name: 
-- Module Name:    commutate - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity commutate is
    Port ( pwm : in   STD_ULOGIC;
           h   : in   STD_ULOGIC_VECTOR (2 downto 0);
           u_l : out  STD_ULOGIC;
           u_h : out  STD_ULOGIC;
           v_l : out  STD_ULOGIC;
           v_h : out  STD_ULOGIC;
           w_l : out  STD_ULOGIC;
           w_h : out  STD_ULOGIC);
end commutate;

architecture Behavioral of commutate is

begin

comm : process (pwm, h )
begin
    case h is
        when "000" => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '0';
            v_h <= '0';
            w_l <= '0';
            w_h <= '0';
        when "001" => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '1';
            v_h <= '0';
            w_l <= '0';
            w_h <= '1';
        when "010" => 
            u_l <= '1';
            u_h <= '0';
            v_l <= '0';
            v_h <= '1';
            w_l <= '0';
            w_h <= '0';
        when "011" => 
            u_l <= '1';
            u_h <= '0';
            v_l <= '0';
            v_h <= '0';
            w_l <= '0';
            w_h <= '1';
        when "100" => 
            u_l <= '0';
            u_h <= '1';
            v_l <= '0';
            v_h <= '0';
            w_l <= '1';
            w_h <= '0';
        when "101" => 
            u_l <= '0';
            u_h <= '1';
            v_l <= '1';
            v_h <= '0';
            w_l <= '0';
            w_h <= '0';
        when "110" => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '0';
            v_h <= '1';
            w_l <= '1';
            w_h <= '0';
        when "111" => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '0';
            v_h <= '0';
            w_l <= '0';
            w_h <= '0';
        when others => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '0';
            v_h <= '0';
            w_l <= '0';
            w_h <= '0';
    end case;
end process;

end Behavioral;

