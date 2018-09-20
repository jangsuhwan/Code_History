
public class Point {
	private double x;
	private double y;
	
	public Point(double x, double y) //constructor
	{
		this.x = x;
		this.y = y;
	}
	
	public double getX() //get method
	{
		return x;
	}
	
	public double getY()
	{
		return y;
	}
	
	public void setX(double x) //set method
	{
		this.x = x;
	}
	
	public void setY(double y)
	{
		this.y = y;
	}
	
	public String toString() //print format
	{
		return String.format("(%.1f,%.1f)", x, y);
	}
}
