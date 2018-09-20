
public class Rectangle {
	private Point topLeftPoint;
	private Point bottomRightPoint;
	
	public Rectangle(double x1, double y1, double x2, double y2) // ��ǥ 4�� �޴� ������
	{
		if(x1>=x2||y1<=y2)// �ùٸ� topLeft�� bottomRight ��ǥ �ޱ�
		{
			System.out.println("not correct Position should be x1<x2 and y1>y2\n");
			System.exit(0);
		}
		Point tp = new Point(x1, y1);
		Point bp = new Point(x2, y2);
		topLeftPoint = tp;
		bottomRightPoint = bp;
	}
	
	public Rectangle(Point p1, Point p2) //������ ��ü �ΰ� �޴� ������
	{
		if(p1.getX()>=p2.getX()||p1.getY()<=p2.getY())
		{
			System.out.println("not correct Position should be x1<x2 and y1>y2\n");
			System.exit(0);
		}
		topLeftPoint = p1;
		bottomRightPoint = p2;
		
	}
	
	
	public Rectangle Union(Rectangle rec) //������ ���簢��
	{
		Rectangle union;
		double ux1, ux2, uy1, uy2;
		double[] rec1t = {this.topLeftPoint.getX(), this.topLeftPoint.getY()}; //rec1�� �»�� x,y
		double[] rec1b = {this.bottomRightPoint.getX(), this.bottomRightPoint.getY()}; //rec1�� ���ϴ� x,y
		double[] rec2t = {rec.topLeftPoint.getX(), rec.topLeftPoint.getY()}; //rec2�� �»�� x,y
		double[] rec2b = {rec.bottomRightPoint.getX(), rec.bottomRightPoint.getY()}; //rec2�� ���ϴ� x,y
		/*���ǹ� ���� : �� ���簢���� ���� �ٸ� ���簢���� ���� ������ ���Եɶ� ���ο� ������ ���
		 ���� �ٸ� ���簢���� ���� ������ ���Ե��� �ʰ� �Ϻκи� ���Եɶ�
		 ��� ���簢���� �ٸ� ���簢���� ��ġ�� �ʴ� ���
		 ���� ��� ������ ��ǥ���� 
		 ������ ���簢�� ���Ҷ��� �������� ������� ��ǥ����.
		 ù��° if�б�� x��ǥ���ϱ�, �ι�° if�б�� y��ǥ ���ϱ�.
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
