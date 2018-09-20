//12131588 장수환
//자료구조 과제 3 AVL TREE 구현
import java.util.*;
class AVLTree
{
	private int data;
	private AVLTree left;
	private AVLTree right;
	private int height;
	AVLTree(int data) {
		this.data = data;
		left = null;
		right = null;
	}
	public int getHeight() {
		return height;
	}
	public void setHeight(int height) {
		this.height = height;
	}
	public int getData() {
		return data;
	}
	
	public void setData(int data){
		this.data = data;
	}
	
	public AVLTree getLeftSubTree(){
		return left;
	}
	
	public AVLTree getRightSubTree(){
		return right;
	}
	
	public void setLeftSubTree(AVLTree sub) {
		if(left != null)
			left = null;
		left = sub;
	}
	
	public void setRightSubTree(AVLTree sub) {
		if(right != null)
			right = null;
		right = sub;
	}
	
	public void InOrder(AVLTree root) //root부터 Inorder 방식으로 출력
	{
		if(root != null) {
			InOrder(root.left);
			System.out.print(root.data+" ");
			InOrder(root.right);
		}
	}
	
	public AVLTree Find(AVLTree root, int e) //root부터 데이터 e를 찾아 해당 데이터 가진 노드 반환
	{
		if(root == null)
			return null;
		if(root.data == e)
			return root;
		else if(root.data > e)
			return Find(root.left, e);
		else
			return Find(root.right, e);
	}
	
	public AVLTree Delete(AVLTree root, int e) { //e를 가진 노드 삭제
		AVLTree p, n; 
		if(root == null)
			return null;
		if(root.getData()==e) {
			AVLTree lt, rt; //왼쪽, 오른쪽 트리
			lt = root.left;
			rt = root.right;
			if(lt == null && rt == null) //두 트리 모두 널 노드면 그냥 삭제하면 되니 null반환
				return null;
			else if(lt == null) //왼쪽만 널이면 오른쪽 트리 반환
			{
				p = rt;
				return p;
			}
			else if(rt == null) //오른쪽만 널이면 왼쪽 트리 반환
			{
				p = lt;
				return p;
			}
			else //양쪽 자식 있을 시에 삭제할 노드보다 큰 수중 가장 작은 노드 왼쪽에 삭제할 노드 왼쪽 자식 트리들을 삽입
			{
				AVLTree temp = root;
				root = root.right;
				AVLTree pNode = root; //가장 작은 노드의 부모
				AVLTree cNode = root; //가장 작은 노드
				while(cNode.left!=null) //가장 작은 노드 찾기
					{
						pNode = cNode;
						cNode = cNode.left;
					}
				
				temp.setData(cNode.getData()); //가장 작은 노드 데이터를 삭제할 노드 데이터로 설정
				
				if(pNode.getData()==cNode.getData()&&cNode.right!=null) //가장 작은 노드가 삭제노드와 오른쪽으로 일직선 일때
					temp.setRightSubTree(cNode.right);
				else if(pNode.getData()==cNode.getData())
					temp.setRightSubTree(null);
				else if(cNode.right == null)//일직선이 아닐때 가장 작은 노드의 오른쪽 자식들이 없을 때
					{
						pNode.setLeftSubTree(null);
						temp.setRightSubTree(root);
					}
				else
					{
						pNode.setLeftSubTree(cNode.right);//일직선이 아닐때 가장 작은 노드의 오른쪽 자식들 있을때
						temp.setRightSubTree(root);
					}
				cNode = null;
				pNode = null;
				return temp; 
			}
		}
		if(e < root.getData())
		{
			n = Delete(root.left, e);
			root.setLeftSubTree(n);
			
		}
		else
		{
			n = Delete(root.right, e);
			root.setRightSubTree(n);
		}

		return root;	
	}
	void resetHeight(AVLTree root)//root부터 시작해서 높이 설정해주는 메서드
	{
		int height = 0;
		
		if(root == null) {
			return;
		}
		if(root.left == null && root.right == null)
		{
			root.setHeight(0);
			return;
		}
		if(root.left != null)
		{
			resetHeight(root.getLeftSubTree());
			height = root.gHeight(root.left);
		}
		if(root.right != null) {
			resetHeight(root.getRightSubTree());
			height = Math.max(height, root.gHeight(root.right));
		}
		root.setHeight(height+1);
			
	}
	public AVLTree ReRotate(AVLTree root)//delete 후 무너진 균형 맞추기 위한 메서드
	{
		/*
		 * 루트 기준 왼쪽과 오른쪽 키 비교해서 더 큰 높이 쪽으로 이동 후
		 * root의 자식기준 왼쪽과 오른쪽 높이 비교 후
		 * 회전방법 결정
		 */
		if(gHeight(right)>gHeight(left)) 
			{
			AVLTree RChild = right;
			if(RChild.gHeight(RChild.left)==RChild.gHeight(RChild.right))
				root = DoubleRotatewithRight(root);
			else if(RChild.gHeight(RChild.left) < RChild.gHeight(RChild.right))
				root = SingleRotateRight(root);
			else
				root = DoubleRotatewithRight(root);
				
			}
		else 
		{
			AVLTree LChild = left;
			if(LChild.gHeight(LChild.left)==LChild.gHeight(LChild.right))
				root = SingleRotateLeft(root);
			else if(LChild.gHeight(LChild.left) > LChild.gHeight(LChild.right))
				root = SingleRotateLeft(root);
			else
				root = DoubleRotatewithLeft(root);
		}
		return root;
	}
	
	public int gHeight(AVLTree root) { //root의 높이 얻는 메서드
		if(root == null) return -1;
		else
			return root.getHeight();
	}
	
	public AVLTree SingleRotateLeft(AVLTree X)//left-left rotation
	{
		//X의 왼쪽을 W설정 후 X의 왼쪽을 W의 오른쪽으로 세팅 후 W의 오른쪽을 X로 세팅
		AVLTree W = X.left;
		X.setLeftSubTree(W.right);
		W.setRightSubTree(X);
		X.setHeight(Math.max(X.gHeight(X.left), X.gHeight(X.right))+1);
		W.setHeight(Math.max(W.gHeight(W.right), W.gHeight(W.left))+1);
		return W;
	}
	public AVLTree SingleRotateRight(AVLTree X)//right-right rotation
	{
		AVLTree W = X.right;
		X.setRightSubTree(W.left);
		W.setLeftSubTree(X);
		X.setHeight(Math.max(X.gHeight(X.left), X.gHeight(X.right))+1);
		W.setHeight(Math.max(W.gHeight(W.left), W.gHeight(W.right))+1);
		return W;
	}
	public AVLTree DoubleRotatewithLeft(AVLTree Z) {//left-right rotation
		//Z의 왼쪽자식을 R-R회전 후 Z의 왼쪽으로 재 세팅 후 Z를 L-L회전 
		Z.setLeftSubTree(SingleRotateRight(Z.getLeftSubTree()));
		return SingleRotateLeft(Z);
	}
	public AVLTree DoubleRotatewithRight(AVLTree Z) {//right-left rotation
		//Z의 오른쪽자식을 L-L회전 후 Z의 오른쪽으로 재 세팅 후 Z를 R-R회전
		Z.setRightSubTree(SingleRotateLeft(Z.getRightSubTree()));
		return SingleRotateRight(Z);
	}
	public AVLTree Insert(AVLTree root, AVLTree parent, int e) { //root기준으로 데이터 e를 찾아가며 삽입과 동시에 균형조절
		if(root == null)
		{
			root = new AVLTree(e);
			root.setLeftSubTree(null);
			root.setRightSubTree(null);
			root.setHeight(0);
		}
		else if(root.getData() > e)
		{
			root.setLeftSubTree(Insert(root.left, root, e));
			if(Math.abs(root.gHeight(root.left)-root.gHeight(root.right))==2) //삽입 후 높이차가 2되면 균형 깨졌으므로 조절
			{
				if(e < root.left.getData())
					root = root.SingleRotateLeft(root);
				else
					root = root.DoubleRotatewithLeft(root);
			}
		}
		else if(root.getData() < e)
		{
			root.setRightSubTree(Insert(root.right, root, e));
			if(Math.abs(root.gHeight(root.right)- root.gHeight(root.left))==2)
			{
				if(e > root.right.getData())
					root = root.SingleRotateRight(root);
				else 
					root = root.DoubleRotatewithRight(root);
			}
		}
		root.setHeight(Math.max(gHeight(root.left), gHeight(root.right))+1);
		
		return root;
	}
	public AVLTree IsAVL(AVLTree root)//Tree의 균형이 무너진 노드 확인하며 없을 시 NULL리턴 있을시 최초 무너진 노드 반환, ReRotate시 인자로 넣어줄 노드
	{
		AVLTree unb = null;
		if(root != null)
		{
			int leftH = root.gHeight(root.left);
			int rightH = root.gHeight(root.right);
			
			if(Math.abs(leftH-rightH)>=2)		
				return unb = root;
			
			if(unb == null)
				unb = IsAVL(root.left);
			if(unb == null)
				unb = IsAVL(root.right);
		}
		return unb;
	}
};

public class DS3_AVLTree_12131588
{
	public static void Exit()
	{
		System.exit(0);
	}
	
	public static void Height(AVLTree root, int e)
	{
		AVLTree node = root.Find(root, e);
		System.out.print(node.gHeight(node)+" "+node.gHeight(node.getLeftSubTree())+" "+node.gHeight(node.getRightSubTree()));
		System.out.println();
	}
	
	public static void Print(AVLTree root)
	{
		if(root == null)
			{System.out.println();
			return;
			}
		root.InOrder(root);
		System.out.println();
	}
	
	public static AVLTree Erase(AVLTree root, int e)//삭제 후 균형 맞추는 메서드
	{
		root = root.Delete(root, e);
		if(root == null)
			return null;
		if(root != null);
			{root.resetHeight(root);
			}
		AVLTree unb = null;
		
		while((unb = root.IsAVL(root))!=null)//데이터 삭제 후 균형 무너진 곳 조절 루프
		{//IsAVL로 무너진 지점 찾고 그 부분부터 조절
			if(unb.getData()==root.getData())
				{
					root = unb.ReRotate(unb);
					root.resetHeight(root);
					break;
				}
			else
			{
				int point = unb.getData();//무너진 지점 데이터
				unb = unb.ReRotate(unb);//균형 조절 한 서브트리
				AVLTree pNode = root;
				AVLTree cNode = root;
				while(cNode.getData()!=point)
				{
					pNode = cNode;
					if(cNode.getData()<point)
						cNode = cNode.getRightSubTree();
					else
						cNode = cNode.getLeftSubTree();	
				}
				if(point<pNode.getData())
					pNode.setLeftSubTree(unb);
				else
					pNode.setRightSubTree(unb);
				root.resetHeight(root);
			}
		}
		return root;
	}
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		AVLTree root = null;
		int method=0, e = 0;
		while(true)
		{
			method = sc.nextInt();
			switch(method)
			{
			case 0:
				Exit();
			case 4:
				Print(root);
				continue;
			}
			if(method!=4||method!=0)
				e = sc.nextInt();
			switch(method)
			{
				case 1:
					if(root == null)
						root = new AVLTree(e);
					else
						root = root.Insert(root, root, e);
					break;
				case 2:
					root = Erase(root, e);
					break;
				case 3:
					Height(root, e);
					break;
			}
		}
	}
}
