//============================================================================
// Name        : SudokuGame.java
// Author      : Shuo Wang (github.com/surew963)
// Version     : 2016-10-19
// Description : Sudoku Game (generator and solver) in Java
//============================================================================
import java.util.*;
    
public class SudokuGame{
	static void show(char [][] board){
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				System.out.print(board[i][j]+" ");
			}
			System.out.println();
		}
		System.out.println("Please enter g to get new game, s to solve, or e to exit.");
	}
    static boolean dfs(char[][] board, boolean [][][] tb, int k) {
        while (k < 81 && board[k/9][k%9] != '.') k++;
        if(k == 81) return true;
        int i = k/9, j = k%9;
        for (char c = '1'; c <= '9'; c++) {
            int ic = c-'1';
            if ((tb[0][i][ic]|tb[1][j][ic]|tb[2][i/3*3+j/3][ic]) != true) {
                tb[0][i][ic] = tb[1][j][ic] = tb[2][i/3*3+j/3][ic] = true;
                board[i][j] = c;
                if (dfs(board, tb, k+1)) return true;
                tb[0][i][ic] = tb[1][j][ic] = tb[2][i/3*3+j/3][ic] = false;
            }
        }
        board[i][j] = '.';
        return false;
    }
    static void solve(char[][] board, boolean [][][] tb) {
        boolean solved = dfs(board, tb, 0);
        if (solved == false) System.out.println("No solution.");
        else show(board);
    }
    static void getNew(char[][] board, boolean [][][] tb){
        for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) {
        		board[i][j] = '.';
        		tb[0][i][j] = tb[1][i][j]=tb[2][i][j] = false;
        	}
        }
        int cnt = 18, c2 = 1;
    	Random rand = new Random();
        while (cnt > 0) {
            int k = rand.nextInt(81), c =(c2++)%9, i = k/9, j = k%9;;
            if (board[i][j] == '.' && (tb[0][i][c]|tb[1][j][c]
            		|tb[2][i/3*3+j/3][c]) == false) {
                board[i][j] = (char)('1'+c);
                tb[0][i][c] = tb[1][j][c] = tb[2][i/3*3+j/3][c] = true;
                cnt--;
            } else {
                c2--;
            }
        }
    }
    static void get(char[][] board, boolean [][][] tb){
    	getNew(board, tb);
    	while(dfs(board, tb, 0) == false) getNew(board, tb);
    	int cnt = 80;
    	Random rand = new Random();
        while (cnt-- > 0) {
            int k = rand.nextInt(81), i = k/9, j = k%9;;
            if (board[i][j] != '.') {
                int c = board[i][j] - '1';
                board[i][j] = '.';
                tb[0][i][c] = tb[1][j][c] = tb[2][i/3*3+j/3][c] = false;
            }
        }
        show(board);
    }
    
    public static void main(String args[]){
    	char [][] board = new char[9][9];
        boolean [][][] tb = new boolean[3][9][9];
	    Scanner sc = new Scanner(System.in);
	    System.out.println("Welcome to Sudoku game.");
	    get(board, tb);
	    while (true) {
		    char c = sc.next().charAt(0);
	        if (c == 'g') get(board, tb);
	        else if (c == 's') solve(board, tb);
	        else if (c == 'e') break;
	        else {
	        	System.out.println("Invalid input. Enter g to get new game, s to solve, or e to exit.");
	        }
	    }
	    sc.close();
    }
}