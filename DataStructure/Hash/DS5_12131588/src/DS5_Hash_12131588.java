import java.util.*;
//double hashing
enum State //each room state  
{
	ERASED, OCCUPIED, EMPTY; 
}
class Table
{
	short key;//store primary key
	State state = State.EMPTY;//init state
}
class HashClass
{
	final static int SIZE = 256;
	int init, jump, bin, start = 1; //init : lower 8bit, jump : higher 8bit, bin : search room index, start : multiple at jump(1*jump, 2*jump... 
	boolean printFlag = true; //printable NOT FOUND if Search is called
	Table table[] = new Table[SIZE];
	public HashClass(){
		for(int i = 0; i<SIZE; i++)
			table[i] = new Table();
	}
	public void setInitAndJump(short key) //init, jump, bin, start set
	{
		init = hash_M1(key); 
		jump = hash_M2(key);
		if(jump < 0)
			jump = -jump;
		bin = init;
		start = 1;
	}
	int hash_M1(short key){
		return (key&((1<<8) - 1));
	}
	int hash_M2(short key) {
		int upperbit = (key&(~((1<<8)-1)))>>8;
		upperbit = upperbit & ((1<<8)-1);
		//make jump with odd
		if((upperbit&1)==1)
			return upperbit;
		else
			return upperbit+1;
	}
	public void Insert(short key){
		printFlag = false;
		if(IsKey(key)==true)//if key is already in table, immediately return
			return;
		setInitAndJump(key);//set necessary values
		while(true)
		{
			bin &= ((1<<8) - 1);//Mod SIZE
			if(!table[bin].state.equals(State.OCCUPIED)) {//if room of bin is not occupied, then key insert and state change to OCCUPIED
				table[bin].key = key;
				table[bin].state = State.OCCUPIED;
				printFlag = true;
				return;
			}
			else
				bin = init + (start++)*jump; 
		}
	}
	public void Erase(short key) {
		setInitAndJump(key);
		while(true)
		{
			bin &= ((1<<8) - 1);
			if(table[bin].state.equals(State.EMPTY))//if empty meet, the key not exist in table, return
				return;
			if(table[bin].state.equals(State.OCCUPIED)) {//if state of room is OCCUPIED, 
				if(table[bin].key == key) //if key of rooom match key which we want to delete, 
				{
					table[bin].state = State.ERASED; //change state with ERASED
					return;
				}
			}
				bin = init + (start++)*jump;
		}
	}
	public int Search(short key) {
		setInitAndJump(key);
		while(true)
		{
			bin = bin&((1<<8) - 1);
			if(table[bin].state.equals(State.EMPTY)) //if empty meet, the key not exist in table, return
				{
				if(printFlag==true)
					System.out.println("NOT FOUND");
				return -1;}
			if(table[bin].state.equals(State.OCCUPIED)) {//if state of room is OCCUPIED,
				if(table[bin].key == key)//if key of rooom match key which we want to find,
				{
					if(printFlag==true)
					System.out.println(key);
					return 0;
				}
			}
				bin = init + (start++)*jump;
		}
	}
	public void Print() {//all room print
		State curstate;
		for(int i = 0; i<SIZE; i++)
		{
			curstate = table[i].state;
			switch(curstate)
			{
			case EMPTY:
				System.out.print("EMPTY ");
				break;
			case OCCUPIED:
				System.out.print(table[i].key+" ");
				break;
			case ERASED:
				System.out.print("DELETED ");
				break;
			}
		}
		System.out.println();
	}
	public boolean IsKey(short key){//confirm key exist
		return Search(key)==0 ? true : false;
	}
	
}
public class DS5_Hash_12131588
{
	public static void main(String[] args)
	{
		HashClass object = new HashClass();
		Scanner sc = new Scanner(System.in);
		int methodNum;
		short key;
		while(true)
		{
			methodNum = sc.nextInt();
			if(methodNum==4)
				{object.Print();
				continue;
				}
			if(methodNum==0)
				System.exit(0);
			key = sc.nextShort();
			switch(methodNum)
			{
			case 1:
				object.Insert(key);
				break;
			case 2:
				object.Erase(key);
				break;
			case 3:
				object.Search(key);
				break;
			}
		}
	}
}