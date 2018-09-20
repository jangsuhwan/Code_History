
public class Rectangle {
	private Point topLeftPoint;
	private Point bottomRightPoint;
	
	public Rectangle(double x1, double y1, double x2, double y2) // 좌표 4개 받는 생성자
	{
		if(x1>=x2||y1<=y2)// 올바른 topLeft와 bottomRight 좌표 받기
		{
			System.out.println("not correct Position should be x1<x2 and y1>y2\n");
			System.exit(0);
		}
		Point tp = new Point(x1, y1);
		Point bp = new Point(x2, y2);
		topLeftPoint = tp;
		bottomRightPoint = bp;
	}
	
	public Rectangle(Point p1, Point p2) //포인터 객체 두개 받는 생성자
	{
		if(p1.getX()>=p2.getX()||p1.getY()<=p2.getY())
		{
			System.out.println("not correct Position should be x1<x2 and y1>y2\n");
			System.exit(0);
		}
		topLeftPoint = p1;
		bottomRightPoint = p2;
		
	}
	
	
	public Rectangle Union(Rectangle rec) //합집합 직사각형
	{
		Rectangle union;
		double ux1, ux2, uy1, uy2;
		double[] rec1t = {this.topLeftPoint.getX(), this.topLeftPoint.getY()}; //rec1의 좌상단 x,y
		double[] rec1b = {this.bottomRightPoint.getX(), this.bottomRightPoint.getY()}; //rec1의 우하단 x,y
		double[] rec2t = {rec.topLeftPoint.getX(), rec.topLeftPoint.getY()}; //rec2의 좌상단 x,y
		double[] rec2b = {rec.bottomRightPoint.getX(), rec.bottomRightPoint.getY()}; //rec2의 우하단 x,y
		/*조건문 설명 : 한 직사각형의 변이 다른 직사각형의 변에 완전히 포함될때 가로와 세로의 경우
		 변이 다른 직사각형의 변에 완전히 포함되지 않고 일부분만 포함될때
		 어느 직사각형이 다른 직사각형과 겹치지 않는 경우
		 각각 경우 따져서 좌표설정 
		 교집합 직사각형 구할때도 마찬가지 방식으로 좌표구함.
		 첫번째 if분기는 x좌표구하기, 두번째 if분기는 y좌표 구하기.
		*/
		if(rec1t[0]>=rec2t[0] && rec1b[0]<=rec2b[0])
		{
			ux1 = rec2t[0];
			ux2 = rec2b[0];
		}
		else if(rec1t[0]<=rec2t[0] && rec1b[0]>=rec2b[0])
		{
			ux1 = rec1t[0];
			ux2 = rec1b[0];
		}
		else if(rec1t[0]<rec2t[0])
			{
				ux1 = rec1t[0];
				ux2 = rec2b[0];
			}
		else
			{
				ux1 = rec2t[0];
				ux2 = rec1b[0];
			}
		
		if(rec1t[1] <= rec2t[1] && rec1b[1] >= rec2b[1])
		{
			uy1 = rec2t[1];
			uy2 = rec2b[1];
		}
		else if(rec1t[1] >= rec2t[1] && rec1b[1] <= rec2b[1])
		{
			uy1 = rec1t[1];
			uy2 = rec1b[1];
		}
		else if(rec1t[1]>rec2t[1])
		{	
			uy1 = rec1t[1];
			uy2 = rec2b[1];
		}
		else 
		{
			uy1 = rec2t[1];
			uy2 = rec1b[1];
		}
	
		
		union = new Rectangle(ux1, uy1, ux2, uy2);
		return union;
	}
	
	public Rectangle Intersect(Rectangle rec)
	{
		Rectangle intersect;
		double ix1, ix2, iy1, iy2;
		double[] rec1t = {this.topLeftPoint.getX(), this.topLeftPoint.getY()};
		double[] rec1b = {this.bottomRightPoint.getX(), this.bottomRightPoint.getY()};
		double[] rec2t = {rec.topLeftPoint.getX(), rec.topLeftPoint.getY()};
		double[] rec2b = {rec.bottomRightPoint.getX(), rec.bottomRightPoint.getY()};
		
		if(rec1t[0]>=rec2t[0] && rec1b[0]<=rec2b[0])
		{
			ix1 = rec1t[0];
			ix2 = rec2b[0];
		}
		else if(rec1t[0]<=rec2t[0] && rec1b[0]>=rec2b[0])
		{
			ix1 = rec2t[0];
			ix2 = rec2b[0];
		}
		else if(rec1t[0]<rec2t[0])
			{
				if(rec1b[0]<=rec2t[0])
					return null;
				ix1 = rec2t[0];
				ix2 = rec1b[0];
			}
		else
			{
				if(rec2t[0]<=rec1b[0])
					return null;
				ix1 = rec1t[0];
				ix2 = rec2b[0];
			}
		
		if(rec1t[1] <= rec2t[1] && rec1b[1] >= rec2b[1])
		{
			iy1 = rec1t[1];
			iy2 = rec1b[1];
		}
		else if(rec1t[1] >= rec2t[1] && rec1b[1] <= rec2b[1])
		{
			iy1 = rec2t[1];
			iy2 = rec2b[1];
		}
		else if(rec1t[1]>rec2t[1])
		{	
			if(rec1b[1]>=rec2t[1])
				return null;
			iy1 = rec2t[1];
			iy2 = rec1b[1];
		}
		else 
		{
			if(rec1t[1]<=rec2b[1])
				return null;
			iy1 = rec1t[1];
			iy2 = rec2b[1];
		}
	
		intersect = new Rectangle(ix1, iy1, ix2, iy2);
		return intersect;
	}
	public String toString()
	{
		return String.format("This rectangle has top left point is %s, width = %.1f, height = %.1f",
				topLeftPoint.toString(), bottomRightPoint.getX()-topLeftPoint.getX(), topLeftPoint.getY()-bottomRightPoint.getY());
	}
}
