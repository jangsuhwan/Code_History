//12131588 장수환 17.09.15
//HW2_지뢰찾기

import java.util.*;

class GameMatrix //게임판 만드는 클래스
{
	private static GameMatrix matrix; 
	private static int row, column, n; 
	static int[][] mines;
	
	private GameMatrix() {};
	
	public static GameMatrix getInstance() { //게임판 만드는 객체 한개만 생성
		if(GameMatrix.matrix == null) {
			matrix = new GameMatrix();
		}
		return matrix;
	}
	
	public void inputData() //게임판에 필요한 속성들 입력받고 저장
	{
		Scanner sc = new Scanner(System.in);
		do {
			System.out.print("Enter the number rows: ");
			row=sc.nextInt();
			System.out.print("Enter the number columns: ");
			column=sc.nextInt();
			System.out.print("Enter the number bomb: ");
			n=sc.nextInt();
		}while(row<0||row>1000||column<0||column>1000||n>row*column);
		mines = new int[row+2][column+2];
	}
	
	public void setMine() //게임판에 지뢰 저장
	{
		Random random = new Random();
		int x, y;
		while(n>=1)
		{
			x = random.nextInt(row+1);
			y = random.nextInt(column+1);
			if(x==0)
				x+=1;
			if(y==0)
				y+=1;
			if(mines[x][y] == -1);
			else
				{
					mines[x][y] = -1; //set mine
					n -= 1;
				}
		}
	}
	
	public void setSafeZone() //안전지대 저장
	{
		for(int i = 1; i<=row; i++)
		{
			for(int j = 1; j<=column; j++)
			{
				if(foundMine(i, j)==-1); 
				else
					mines[i][j]=foundMine(i, j);
			}
		}
	}
	
	public int foundMine(int x, int y) //지뢰가 주변에 몇개있는지 찾기
	{
		int numOfMine = 0;
		int x_pos[] = {-1, 0, 1}; // move distance
		int y_pos[] = {-1, 0, 1};
		
		if(mines[x][y]==-1)
			return -1;
		
		for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					int X = x_pos[i] + x;
					int Y = y_pos[j] + y;
					
					if(mines[X][Y]==-1) //주변에 지뢰찾을때마다 숫자 증가시킴
					{
						numOfMine += 1;
					}
				}
			}
		return numOfMine;
	}
	
	public void showMap() //matrix에 저장되있는 값에 따라 출력
	{
		for(int i = 1; i<=row; i++)
			{
				for(int j = 1; j<=column; j++)
				{
					if(mines[i][j]==0)
						System.out.print("- ");
					else if(mines[i][j]==-1)
						System.out.print("* ");
					else
						System.out.printf("%d ", mines[i][j]);
				}
				System.out.println();
			}
	}
}

public class Minesweeper
{
	public static void main(String[] args)
	{
		GameMatrix matrix = GameMatrix.getInstance();
		matrix.inputData();
		matrix.setMine();
		matrix.setSafeZone();
		matrix.showMap();
	}
}