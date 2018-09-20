//12131588 ���ȯ 17.09.15
//HW2_����ã��

import java.util.*;

class GameMatrix //������ ����� Ŭ����
{
	private static GameMatrix matrix; 
	private static int row, column, n; 
	static int[][] mines;
	
	private GameMatrix() {};
	
	public static GameMatrix getInstance() { //������ ����� ��ü �Ѱ��� ����
		if(GameMatrix.matrix == null) {
			matrix = new GameMatrix();
		}
		return matrix;
	}
	
	public void inputData() //�����ǿ� �ʿ��� �Ӽ��� �Է¹ް� ����
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
	
	public void setMine() //�����ǿ� ���� ����
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
	
	public void setSafeZone() //�������� ����
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
	
	public int foundMine(int x, int y) //���ڰ� �ֺ��� ��ִ��� ã��
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
					
					if(mines[X][Y]==-1) //�ֺ��� ����ã�������� ���� ������Ŵ
					{
						numOfMine += 1;
					}
				}
			}
		return numOfMine;
	}
	
	public void showMap() //matrix�� ������ִ� ���� ���� ���
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