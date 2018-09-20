//12131588 Àå¼öÈ¯ HOMEWORK

import java.util.*;

public class main
{
	public static void main(String[] args)
	{
		System.out.println("First case output");
		Point tl1 = new Point(-3, 3); //topleft
		Point br1 = new Point(0, 0); //bottomright
		Point tl2 = new Point(-1, 2); 
		Point br2 = new Point(-0.5, 1);
		
		Rectangle rec1 = new Rectangle(tl1, br1);
		Rectangle rec2 = new Rectangle(tl2, br2);
		
		Print(rec1, rec2);
		
		System.out.println("\nSecond case output");
		Rectangle rec3 = new Rectangle(-7, 5, 0, 0);
		Rectangle rec4 = new Rectangle(-2.5, -2, -1, -3.5);
		
		Print(rec3, rec4);
	}
	
	public static void Print(Rectangle rec1, Rectangle rec2)
	{
		System.out.println("rec1\n"+rec1);
		System.out.println("rec2\n"+rec2);
		
		Rectangle Union = rec1.Union(rec2);
		System.out.println("Union Rectangle\n"+Union);
		
		Rectangle inter = rec1.Intersect(rec2);
			
		if(inter == null)
			System.out.println("These two Objects rectangle 1 and "
					+ "rectangle2 has no intersection");
		else
			System.out.println("Intersect Rectangle\n"+inter);
	}
}