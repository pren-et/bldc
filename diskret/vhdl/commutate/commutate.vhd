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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity commutate is
    generic (
        CLK_FRQ : integer := 50_000_000; -- 50 MHz
        PWM_FRQ : integer := 285
        );
    Port ( clk : in   STD_ULOGIC;
           rst : in   STD_ULOGIC;
           sw  : in   STD_ULOGIC_VECTOR (3 downto 0);
           h   : in   STD_ULOGIC_VECTOR (2 downto 0);
           led : out  STD_ULOGIC_VECTOR (7 downto 0);
           u_l : out  STD_ULOGIC;
           u_h : out  STD_ULOGIC;
           v_l : out  STD_ULOGIC;
           v_h : out  STD_ULOGIC;
           w_l : out  STD_ULOGIC;
           w_h : out  STD_ULOGIC;
           h_b : out  STD_ULOGIC);
end commutate;

architecture Behavioral of commutate is

signal h_buffered : STD_ULOGIC_VECTOR (2 downto 0);
signal pwm        : STD_ULOGIC;
signal pwm_clk    : STD_ULOGIC;
signal div_cnt    : unsigned (15 downto 0);
signal pwm_cnt    : STD_ULOGIC_VECTOR (3 downto 0);

begin

f_div : process (rst, clk)
begin
    if rst = '1' then
        div_cnt <= (others => '0');
        pwm_clk <= '0';
    elsif rising_edge(clk) then
        if div_cnt = to_unsigned(0, 16) then
            div_cnt <= to_unsigned(156, 16);
            pwm_clk <= '1';
        else
            div_cnt <= div_cnt - 1;
            pwm_clk <= '0';
        end if;
    end if;
end process;

p_pwm : process (rst, clk, pwm_clk, sw)
begin
    if rst = '1' then
        pwm_cnt <= "0000";
        pwm <= '0';
    elsif rising_edge(clk) then
        if pwm_clk = '1' then
            if pwm_cnt = "1111" then
                pwm_cnt <= "0000";
            else
                pwm_cnt <= std_ulogic_vector(unsigned(pwm_cnt) + 1);
            end if;
            if pwm_cnt < sw then
                pwm <= '1';
            else
                pwm <= '0';
            end if;
        end if;
    end if;
end process;

h_buffer : process (pwm, h)
begin
    if falling_edge(pwm) then
        h_buffered <= h;
    else
        h_buffered <= h_buffered;
    end if;
end process;

h_b <= h_buffered(0);
led(0) <= not h(0);
led(1) <= not h(1);
led(2) <= not h(2);
led(3) <= pwm;
led(4) <= pwm_clk;
led(5) <= '0';
led(6) <= '0';
led(7) <= '0';

comm : process (pwm, h_buffered )
begin
    case h_buffered is
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
            v_l <= pwm;
            v_h <= '0';
            w_l <= '0';
            w_h <= pwm;
        when "010" => 
            u_l <= pwm;
            u_h <= '0';
            v_l <= '0';
            v_h <= pwm;
            w_l <= '0';
            w_h <= '0';
        when "011" => 
            u_l <= pwm;
            u_h <= '0';
            v_l <= '0';
            v_h <= '0';
            w_l <= '0';
            w_h <= pwm;
        when "100" => 
            u_l <= '0';
            u_h <= pwm;
            v_l <= '0';
            v_h <= '0';
            w_l <= pwm;
            w_h <= '0';
        when "101" => 
            u_l <= '0';
            u_h <= pwm;
            v_l <= pwm;
            v_h <= '0';
            w_l <= '0';
            w_h <= '0';
        when "110" => 
            u_l <= '0';
            u_h <= '0';
            v_l <= '0';
            v_h <= pwm;
            w_l <= pwm;
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

