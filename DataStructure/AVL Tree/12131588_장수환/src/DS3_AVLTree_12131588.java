//12131588 ���ȯ
//�ڷᱸ�� ���� 3 AVL TREE ����
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
	
	public void InOrder(AVLTree root) //root���� Inorder ������� ���
	{
		if(root != null) {
			InOrder(root.left);
			System.out.print(root.data+" ");
			InOrder(root.right);
		}
	}
	
	public AVLTree Find(AVLTree root, int e) //root���� ������ e�� ã�� �ش� ������ ���� ��� ��ȯ
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
	
	public AVLTree Delete(AVLTree root, int e) { //e�� ���� ��� ����
		AVLTree p, n; 
		if(root == null)
			return null;
		if(root.getData()==e) {
			AVLTree lt, rt; //����, ������ Ʈ��
			lt = root.left;
			rt = root.right;
			if(lt == null && rt == null) //�� Ʈ�� ��� �� ���� �׳� �����ϸ� �Ǵ� null��ȯ
				return null;
			else if(lt == null) //���ʸ� ���̸� ������ Ʈ�� ��ȯ
			{
				p = rt;
				return p;
			}
			else if(rt == null) //�����ʸ� ���̸� ���� Ʈ�� ��ȯ
			{
				p = lt;
				return p;
			}
			else //���� �ڽ� ���� �ÿ� ������ ��庸�� ū ���� ���� ���� ��� ���ʿ� ������ ��� ���� �ڽ� Ʈ������ ����
			{
				AVLTree temp = root;
				root = root.right;
				AVLTree pNode = root; //���� ���� ����� �θ�
				AVLTree cNode = root; //���� ���� ���
				while(cNode.left!=null) //���� ���� ��� ã��
					{
						pNode = cNode;
						cNode = cNode.left;
					}
				
				temp.setData(cNode.getData()); //���� ���� ��� �����͸� ������ ��� �����ͷ� ����
				
				if(pNode.getData()==cNode.getData()&&cNode.right!=null) //���� ���� ��尡 �������� ���������� ������ �϶�
					temp.setRightSubTree(cNode.right);
				else if(pNode.getData()==cNode.getData())
					temp.setRightSubTree(null);
				else if(cNode.right == null)//�������� �ƴҶ� ���� ���� ����� ������ �ڽĵ��� ���� ��
					{
						pNode.setLeftSubTree(null);
						temp.setRightSubTree(root);
					}
				else
					{
						pNode.setLeftSubTree(cNode.right);//�������� �ƴҶ� ���� ���� ����� ������ �ڽĵ� ������
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
	void resetHeight(AVLTree root)//root���� �����ؼ� ���� �������ִ� �޼���
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
	public AVLTree ReRotate(AVLTree root)//delete �� ������ ���� ���߱� ���� �޼���
	{
		/*
		 * ��Ʈ ���� ���ʰ� ������ Ű ���ؼ� �� ū ���� ������ �̵� ��
		 * root�� �ڽı��� ���ʰ� ������ ���� �� ��
		 * ȸ����� ����
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
	
	public int gHeight(AVLTree root) { //root�� ���� ��� �޼���
		if(root == null) return -1;
		else
			return root.getHeight();
	}
	
	public AVLTree SingleRotateLeft(AVLTree X)//left-left rotation
	{
		//X�� ������ W���� �� X�� ������ W�� ���������� ���� �� W�� �������� X�� ����
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
		//Z�� �����ڽ��� R-Rȸ�� �� Z�� �������� �� ���� �� Z�� L-Lȸ�� 
		Z.setLeftSubTree(SingleRotateRight(Z.getLeftSubTree()));
		return SingleRotateLeft(Z);
	}
	public AVLTree DoubleRotatewithRight(AVLTree Z) {//right-left rotation
		//Z�� �������ڽ��� L-Lȸ�� �� Z�� ���������� �� ���� �� Z�� R-Rȸ��
		Z.setRightSubTree(SingleRotateLeft(Z.getRightSubTree()));
		return SingleRotateRight(Z);
	}
	public AVLTree Insert(AVLTree root, AVLTree parent, int e) { //root�������� ������ e�� ã�ư��� ���԰� ���ÿ� ��������
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
			if(Math.abs(root.gHeight(root.left)-root.gHeight(root.right))==2) //���� �� �������� 2�Ǹ� ���� �������Ƿ� ����
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
	public AVLTree IsAVL(AVLTree root)//Tree�� ������ ������ ��� Ȯ���ϸ� ���� �� NULL���� ������ ���� ������ ��� ��ȯ, ReRotate�� ���ڷ� �־��� ���
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
	
	public static AVLTree Erase(AVLTree root, int e)//���� �� ���� ���ߴ� �޼���
	{
		root = root.Delete(root, e);
		if(root == null)
			return null;
		if(root != null);
			{root.resetHeight(root);
			}
		AVLTree unb = null;
		
		while((unb = root.IsAVL(root))!=null)//������ ���� �� ���� ������ �� ���� ����
		{//IsAVL�� ������ ���� ã�� �� �κк��� ����
			if(unb.getData()==root.getData())
				{
					root = unb.ReRotate(unb);
					root.resetHeight(root);
					break;
				}
			else
			{
				int point = unb.getData();//������ ���� ������
				unb = unb.ReRotate(unb);//���� ���� �� ����Ʈ��
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
