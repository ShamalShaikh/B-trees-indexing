#include<bits/stdc++.h>
#include<bits/stdc++.h>
using namespace std;
#define d 2

typedef struct bdnode{
	int cnt;
	int key[2*d+5];
	bdnode *ptr[2*d+2+5];
//	int *key;
//	int **ptr;
}*BDPTR;

int marker = 0;
BDPTR Add(BDPTR &T,int k,int flag2,BDPTR t);
void del(BDPTR &T, int k);
void del_util(BDPTR &X,int k,int index1,BDPTR p,BDPTR main_tree);

int check_leaf_node(BDPTR T){
		int flag1 = 1;
		for(int i=0;i<T->cnt;++i)
		{
			if(T->ptr[i]!=NULL)
			flag1=0;
		}
		return flag1;
}


void levelOrderPrint(BDPTR T){      //Function to print Level Order
		queue<BDPTR> q;
		int flag=0;
		BDPTR temp=T,X=NULL;
		q.push(T);
		q.push(X);
		while(!q.empty()){
			temp = q.front();
			q.pop();
			if(temp == NULL){
				cout<<"\n";
				if(!q.empty())
					q.push(X);
			}
			else{
				//printing the node
				for(int i= 0;i<temp->cnt;i++){
					cout<<temp->key[i]<<",";
					if (temp->ptr[i])
					q.push(temp->ptr[i]);
				}
				cout<<"\b";
//				cout<<"#####"<<"\n";
				
				if (temp->ptr[temp->cnt])
				q.push(temp->ptr[temp->cnt]);
				cout<<"   ";
			}
		}
}
//construct Bd-Tree
bool Overflow(BDPTR D){
	if(D->cnt > 2*d)
	return true;
	return false;
}

bool underflow(BDPTR D){
	if(D==NULL)
	return false;
	if(D->cnt<=d)
	return true;
	return false;
}

void sort(BDPTR &D,int n){  
    int i, key, j;  
    for (i = 1; i < n; i++) 
    {  
       key = D->key[i];  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && D->key[j] > key) 
        {  
            D->key[j + 1] = D->key[j];  
           j = j - 1;  
        }  
        D->key[j + 1] = key;  
    }    
}

void SortwithPTR(BDPTR &t,int n){
	  int i, key, j;  
	  BDPTR pkey;
    for (i = 1; i < n; i++) 
    {  
        key = t->key[i]; 
		pkey = t->ptr[i+1]; 
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && t->key[j] > key) 
        {  
            t->key[j + 1] = t->key[j];  
            t->ptr[j+1+1] = t->ptr[j+1];
            j = j - 1;  
        }  
        t->key[j + 1] = key;
		t->ptr[j+1+1] = pkey;  
    } 
}
int get_index_in_parent(BDPTR T,BDPTR &t){
	if(t==NULL)return -1;
	for(int i=0;i<t->cnt +1;i++){
		if(t->ptr[i]==T)
		return i;
	}
	return -1;
}

int findMedian(BDPTR &D,int k){
	sort(D,D->cnt);
//	sortwithPTR(D,D->cnt);
	return D->key[D->cnt/2];
}

BDPTR createNewNodeBstar(BDPTR T,BDPTR t){
	SortwithPTR(T,T->cnt);
	int index2 = get_index_in_parent(T,t);
	BDPTR temp =new bdnode;
	for(int i=0;i<2*d+1;++i)
	temp->ptr[i]=NULL;
	
	temp->cnt = (4*d/3);
	int i,j;
	for( i=0,j=(T->cnt/3)+1;j<(T->cnt);++i,++j)
	{
		temp->key[i] = T->key[j];
		
		if(T->ptr[j])
		{
			temp->ptr[i] = T->ptr[j];
		}
		else temp->ptr[i] = NULL;
	}
	if(T->ptr[j])
	temp->ptr[i] = T->ptr[j];
	else
	temp->ptr[i] = NULL;
	
	for(j=0;j<(t->ptr[index2+1]->cnt)/3;++i,++j){
		temp->key[i] = t->ptr[index2 +1]->key[j];
		if(t->ptr[index2+1]->ptr[j])
		{
			temp->ptr[i] = t->ptr[index2+1]->ptr[j];
		}
		else temp->ptr[i] = NULL;
	}
	if(t->ptr[index2+1]->ptr[j])
	temp->ptr[i] = T->ptr[j];
	else
	temp->ptr[i] = NULL;
	
	
	return temp;
}

BDPTR createNewNode(BDPTR T){
	BDPTR temp =new bdnode;
	for(int i=0;i<2*d+1;++i)
	temp->ptr[i]=NULL;
	
	temp->cnt = (T->cnt/2);
	int i,j;
	for( i=0,j=(T->cnt/2)+1;j<(T->cnt);++i,++j)
	{
		temp->key[i] = T->key[j];
		if(T->ptr[j])
		{
			temp->ptr[i] = T->ptr[j];
		}
		else temp->ptr[i] = NULL;
	}
	if(T->ptr[j])
	temp->ptr[i] = T->ptr[j];
	else
	temp->ptr[i] = NULL;
	
	return temp;
}


int getMedianIndex(BDPTR t,int median){
	int s;
	for(s=0;s<t->cnt;++s)
		if(t->key[s] == median)
		return s;
	return s;	
}

BDPTR adjust(BDPTR t,BDPTR T,BDPTR temp,int median){
	if(t->cnt == 1)
	{
		t->ptr[0] = T;
		t->ptr[1] = temp;
	}
	else{
		int MedianIndex = getMedianIndex(t,median);
		cout<<"Median_index"<<MedianIndex<<"\n"<<T->key[0]<<" " <<t->key[0]<<" "<<temp->key[0]<<"\n";
		t->ptr[MedianIndex] = T;
		t->ptr[MedianIndex+1] = temp;
	}
	
	return t;
	
}

int getIndex(BDPTR T, int k){
	int s;
	for(s=0;s<T->cnt;++s)
		if(T->key[s]>k)
		return s;
	return s;
}

void inorder(BDPTR T){
	if(T==NULL)
	return;
	else{
		int i;
		for(i=0;i<T->cnt;++i)
		{
			inorder(T->ptr[i]);
			cout<<T->key[i];
		}
		if(T->ptr[i])
		inorder(T->ptr[i]);
	}
}
//bool isNull(BDPTR x){
//return x==NULL;}



void left_to_right(BDPTR &T,BDPTR &t,int left_index,BDPTR main_tree){
			//ADD in next sibling
		// del(T,T->key[T->cnt],1,t);
			BDPTR right = t->ptr[left_index +1];
			BDPTR left = t->ptr[left_index];
			int i=t->ptr[left_index+1]->cnt;
		while(i>0){
			right->key[i] = right->key[i-1]; //right_shift
			right->ptr[i+1] = right->ptr[i];
	//		t->ptr[left_index+1]->ptr[i] = NULL;
			i--;
		}
		right->ptr[i+1] = right->ptr[i]; //last pointer
		right->cnt++;
			right->key[0] = t->key[left_index] ;
			right->ptr[0] = left->ptr[left->cnt];
	//		t->ptr[left_index+1]->ptr[i]=NULL;
//			T->cnt--;
			t->key[left_index] =left->key[left->cnt-1];
		t->ptr[left_index +1] = right;
		left->cnt--;
//			t->ptr[left_index] = left;
//			sort(right,right->cnt);
//			del_util(left, left->key[left->cnt-1], left->cnt-1, t,main_tree);
		//	left_index++;
		//	T->key[T->cnt] = 0;
		
		return;
}
void right_to_left(BDPTR &T,BDPTR &t,int right_index,BDPTR main_tree){
		cout<<T->key[0]<<" came here"<<endl;
		BDPTR left = t->ptr[right_index-1];
		BDPTR right = t->ptr[right_index];
		//ADD in previous sibling
		left->key[left->cnt++]= t->key[right_index-1];
		left->ptr[left->cnt]= right->ptr[0];
		t->key[right_index-1] = right->key[0];
//		T->cnt--;
//		del_util(right, right->key[0], 0, t,main_tree);
		for (int i=0;i<right->cnt-1; i++){
			right->key[i] = right->key[i+1];
			right->ptr[i] = right->ptr[i+1];
		}
		right->ptr[right->cnt-1] = right->ptr[right->cnt];
		right->cnt--;
	//	del_util(left,)
//		int i=1;
//		while(i<right->cnt){
//			right->key[i-1] = right->key[i];
//			right->ptr[i-1] = right->ptr[i];
//			i++;
//		}
//		right->ptr[i-1] = right->ptr[i];
		t->ptr[right_index-1] = left;
		t->ptr[right_index] = right;
		return;
}

bool checkKRdel(BDPTR &T,BDPTR &t,int index, int index1,BDPTR main_tree, bool del = true){
	if(index>0)
	if(t->ptr[index-1])
	if(t->ptr[index-1]->cnt<=d){}
	else{
		for(int i=index1; i<T->cnt-1; i++)
		{
			T->key[i]  = T->key[i+1];
		}
		if(del){
			T->cnt--;
		}
		
		left_to_right(T,t,index-1, main_tree);
		return 1;
	}
	
	if(index<t->cnt)
		if(t->ptr[index+1])
		if(t->ptr[index+1]->cnt<=d){
			return 0;
		}
		else{
			for(int i=index1; i<T->cnt-1; i++)
		{
			T->key[i]  = T->key[i+1];
		}
		if(del){
			T->cnt--;
		}
			right_to_left(T,t,index+1,main_tree);
			
			return 2;
		}
	return 0;		
}

bool checkFULLKRdel(BDPTR &T,BDPTR &t,int index2,int index1,BDPTR main_tree,bool del = true){
	int r;
//	bool flag =true;
	for(int i=0;i<=t->cnt;++i){
		if(!underflow(t->ptr[i])){
			 r = index2 - i;
			 if(r<0){
//			 	flag = false;
			 	for(int a=index1; a<T->cnt-1; a++)
				{
					T->key[a] = T->key[a+1];
					
				}
				if(del){
						T->cnt--;
				}
			 	for(int j = 0; j<abs(r);++j){
			 		right_to_left(t->ptr[i-j],t,i-j,main_tree);
				 }
			 }
			 else if(r>0){
//			 	flag = false;
			 	for(int a=index1; a<T->cnt-1; a++)
				{
					T->key[a]  = T->key[a+1];
				}
				if(del){
					T->cnt--;
				}
			 	for(int j=i;j<r;++j){
			 		left_to_right(t->ptr[j],t,j,main_tree);
				 }
			 }
			 
		return true;
		}
		
	}
//	if(flag){
//			BDPTR t_p = get_parent(T,t);
//			int index3 = get_index_in_parent(t,t_p);
//			if(t_p->ptr[index3+1])
//			{
//				t->ptr[t->cnt++] = t_p->key[index3]; 
//				t_p->key[index3] = minBD();
//				
//			}
//		}
	return false;
}

bool checkFULLKR(BDPTR &T,BDPTR &t,int index1,BDPTR main_tree){
	int r;
	SortwithPTR(T,T->cnt);
	int index2 = get_index_in_parent(T,t);
	for(int i=0;i<=t->cnt;++i){
		if(!t->ptr[i]>=2*d){
			r = index1 - i;
			if(r>0){
				//for(int a = index1)
				for(int l=0;l<r;++l){
					left_to_right(T,t,index2,main_tree);
				}
			}
			else if(r<0){
				for(int l=0;l<r;++l){
					right_to_left(T,t,index2,main_tree);
				}
			} 
		return true;
		}
	}
	
	return false;
}

bool checkKeyRedistribution(BDPTR &T,BDPTR &t,int index,BDPTR main_tree){
	sort(T,T->cnt);
	
	if(index>0)
	if(t->ptr[index-1])
	if(t->ptr[index-1]->cnt>=2*d){}
	else{
		cout<<T->key[0]<<" came here"<<endl;
		//ADD in previous sibling
//		t->ptr[index-1]->key[t->ptr[index-1]->cnt++]= t->key[index-1];
//		t->ptr[index-1]->ptr[t->ptr[index-1]->cnt]= t->ptr[index]->ptr[0];
//		t->key[index-1] = t->ptr[index]->key[0];
//		T->cnt--;
//	//	del(T,T->key[0],1,t);
//		int i=1;
//		while(i<=T->cnt){
//			T->key[i-1] = T->key[i];
//			T->ptr[i-1] = T->ptr[i];
//			i++;
//		
//		}
//		
//		T->ptr[i-1] = T->ptr[i];
		right_to_left(T,t,index,main_tree);
		return true;
	}
		if(index<t->cnt)
		if(t->ptr[index+1])
		if(t->ptr[index+1]->cnt>=2*d){
			return false;
		}
		else{
			//ADD in next sibling
//			int i=t->ptr[index+1]->cnt;
//		while(i>0){
//			t->ptr[index+1]->key[i] = t->ptr[index+1]->key[i-1];
//			t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
//	//		t->ptr[index+1]->ptr[i] = NULL;
//			i--;
//		}
//		t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
//		t->ptr[index+1]->cnt++;
//			t->ptr[index+1]->key[0] = t->key[index] ;
//			t->ptr[index+1]->ptr[0] = t->ptr[index]->ptr[T->cnt];
//	//		t->ptr[index+1]->ptr[i]=NULL;
//			T->cnt--;
//		// del(T,T->key[T->cnt],1,t);
//			t->key[index] =t->ptr[index]->key[T->cnt];
		//	T->key[T->cnt] = 0;
			left_to_right(T,t,index,main_tree);
			return true;
		}

}

//void checkKeyRedistributionDel(BDPTR &T,BDPTR &t,int index){
//	sort(T,T->cnt);
//	
//	if(index>0)
//	if(t->ptr[index-1])
//	if(t->ptr[index-1]->cnt<=2*d){}
//	else{
//			int i=t->ptr[index+1]->cnt;
//		while(i>0){
//			t->ptr[index+1]->key[i] = t->ptr[index+1]->key[i-1];
//			t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
//	//		t->ptr[index+1]->ptr[i] = NULL;
//			i--;
//		}
//		t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
//		t->ptr[index+1]->cnt++;
//			t->ptr[index+1]->key[0] = t->key[index] ;
//			t->ptr[index+1]->ptr[0] = t->ptr[index]->ptr[T->cnt];
//	//		t->ptr[index+1]->ptr[i]=NULL;
//			T->cnt--;
//		// del(T,T->key[T->cnt],1,t);
//			t->key[index] =t->ptr[index]->key[T->cnt];
//		//	T->key[T->cnt] = 0;
//
//	}
//		if(index<=t->cnt)
//		if(t->ptr[index+1])
//		if(t->ptr[index+1]->cnt>=2*d){
//			return;
//		}
//		else{
//			//ADD in next sibling
//				cout<<T->key[0]<<" came here"<<endl;
//		//ADD in previous sibling
//		t->ptr[index-1]->key[t->ptr[index-1]->cnt++]= t->key[index-1];
//		t->ptr[index-1]->ptr[t->ptr[index-1]->cnt]= t->ptr[index]->ptr[0];
//		t->key[index-1] = t->ptr[index]->key[0];
//		T->cnt--;
//	//	del(T,T->key[0],1,t);
//		int i=1;
//		while(i<=T->cnt){
//			T->key[i-1] = T->key[i];
//			T->ptr[i-1] = T->ptr[i];
//			i++;
//		
//		}
//		T->ptr[i-1] = T->ptr[i];
//		return;
//		}
//
//}



BDPTR Add(BDPTR &T,int k,int flag2,BDPTR t){
	int flag1=1;
	int index;
	if(T==NULL){
	T= new bdnode;
	for(int i=0;i<2*d+1;++i)
	T->ptr[i]=NULL;
	T->cnt = 0;
	T->key[T->cnt++] = k;	
	return T;
	}
	else{BDPTR z;
//		for(int i=0;i<T->cnt;++i)
//		{
//			if(T->ptr[i]!=NULL)
//			flag1=0;
//		}
		flag1 = check_leaf_node(T);
		//if leaf node
		if(flag1){
			
			T->key[T->cnt++] = k;
			T->ptr[T->cnt] = NULL;
			cout<<"leaf"<<"\n";
			// OVERFLOW CONDITION
		}
		//not a leaf node
		else{
			 index = getIndex(T,k);
			BDPTR x = Add(T->ptr[index], k,1,T);
			// T->ptr[index] = Add(T->ptr[index], k,1,T);
	}
	
	if(Overflow(T)){
		bool f = false,b = false;
		// check for KEY REDISTRIBUTION
		if((flag2==1)){
			int index = get_index_in_parent(T,t);
		if(index == -1){
			cout<<"T not found in t"<<"\n";
			exit(0);
		}
			cout<<T->key[0]<<" has parent and is at index :"<<index<<"\n";
			f = checkKeyRedistribution(T,t,index,T);
			if(!f){
			//CHECK FOR FULL KEY REDISTRIBUTION
			 b = checkFULLKR(T,t,index,T);
		}
	}
		
		if(Overflow(T)){
			if(!b){
				int median;
			median = findMedian(T,k);
			
//			cout<<"******"<<median<<"\n";
			
//			cout<<isNull(T->ptr[0])<<"\n";
//			cout<<isNull(T->ptr[1])<<"\n";
//			cout<<isNull(T->ptr[2])<<"\n";
			BDPTR temp;
			if(t==NULL)
			 temp = createNewNode(T);
			else
			 temp = createNewNodeBstar(T,t);
//			cout<<isNull(temp->ptr[0])<<"\n";
//			cout<<isNull(temp->ptr[1])<<"\n";
//			cout<<isNull(temp->ptr[2])<<"\n";
			levelOrderPrint(temp);
//			cout<<"******"<<"\n";
//			for(int p= 0;p<temp->cnt;p++){
//				cout<<temp->key[p];
//			}
			if(temp->ptr[0])
			cout<<temp->ptr[0]->key[0];
			if(temp->ptr[1])
				cout<<temp->ptr[1]->key[0];
//			cout<<"\n";
//			for(int p= 0;p<T->cnt;p++){
//				cout<<T->key[p];
//			}
			for(int i=2*(T->cnt/3);i<T->cnt;++i){
				T->key[i] = 0;
//				T->ptr[i+1]= NULL;
			}
			T->cnt = 2*(T->cnt/3);
//			for(int p= 0;p<T->cnt;p++){
//				cout<<T->key[p];
//			}
//			cout<<"******"<<"\n";
			//if parent node is not present
			if(flag2 == 0){
				//createnewNode();
				BDPTR t = new bdnode;
				for(int i=0;i<2*d+1;++i)
				t->ptr[i]=NULL;
				t->cnt = 0;
				t->key[t->cnt++] = median;
//				cout<<"******"<<"\n";
				 z = adjust(t,T,temp,median);
				 
//				for(int p= 0;p<z->cnt;p++){
//				cout<<z->key[p];
//			}
//				cout<<z->ptr[0]->key[0]<<" "<<z->ptr[1]->key[0]<<"\n";
//				
//				
//				cout<<"******"<<"\n";
			}
			else{ //parent present
				
				t->key[t->cnt++] = median;
				SortwithPTR(t,t->cnt);
			//	if(Overflow(t))
					for(int p= 0;p<t->cnt;p++){
				cout<<t->key[p];
			}
//			cout<<"\n";
//			for(int p= 0;p<T->cnt;p++){
//				cout<<T->key[p];
//			}
			cout<<t->ptr[0]->key[0];
//				cout<<t->ptr[1]->key[0];
				 z = adjust(t,T,temp,median); //to adjust pointers 
				//cout<<z->key[0]<< " "<<z->key[1]<<"\n";
				//cout<<z->ptr[0]->key[0]<< " "<<z->ptr[1]->key[0]<<"\n";
			}
			}
		}
			else{
			sort(T,T->cnt);
			z = T;
		}
	//	cout<<"T->data : "<<T->key[0]<<" T->cnt: "<<T->cnt;		check this once!!	
		}
		// NODE STILL NOT FILLED
		else{
			sort(T,T->cnt);
			z = T;
		}
		cout<<"\nTree till now:\n"; 
		if(z)
	levelOrderPrint(z);
	return z;
}
	
}

//int get_index_inNode(BDPTR T,)
BDPTR s;
BDPTR search(BDPTR X,int k,BDPTR &parent,int &index1){
//	static BDPTR D = t;
//	if(X==NULL)
//	return NULL;
//	else{
//		for(int i=0;i<X->cnt;++i)
//		{
//			if(X->key[i]==k)
//			{	index1 = i;
//				return X;	
//			}
//			else
//			if(X->key[i]>k){
//			X = search(X->ptr[i],k,X,index1);
//			}
//		}
//		X =  search(X->ptr[X->cnt],k,X,index1);
//		return X;
//	}
//	
label:
while(X!=NULL){
	for(int i=0;i<X->cnt;i++){
		if(X->key[i]==k)
			{	index1 = i;
				return X;	
			}
			else
			if(X->key[i]>k){
				parent = X;
			X = X->ptr[i];
			//continue;
			goto label;
			}
		}
		parent = X;
		X =  X->ptr[X->cnt];
	}
return X;
}
BDPTR merge_nodes(BDPTR &t1, BDPTR &t2){
	if(t1==NULL)return t2;
	if (t2 ==NULL) return t1;
	int x=0;
	for(int i=0,j = t1->cnt; i<t2->cnt; i++, j++){
		t1->key[j] = t2->key[i];
		x++;
		t1->ptr[j+1] = t2->ptr[i+1];
	}
	t1->ptr[t1->cnt] = merge_nodes(t1->ptr[t1->cnt], t2->ptr[0]);
	t1->cnt+=x;
	t2 = NULL;
	return t1;
}

BDPTR get_parent(BDPTR T, BDPTR t){
	if(t==NULL)
	return NULL;
	if (T==t) return NULL;
	for(int i = 0;i<T->cnt; i++){
		if (T->ptr[i] == t)
		return T;
		if(T->key[i]>t->key[0])
		return get_parent(T->ptr[i], t);
	}
	return get_parent(T->ptr[T->cnt], t);
	
}
void NodeCombine(BDPTR &T, BDPTR &parent,int index2, int index1, BDPTR main_tree){
	
	cout<<T->key[0]<<" in node combine, marker = "<<marker<<" index1 = "<<index1<<" index2= "<<index2<<"\n";
	if(index2 == 0){
		BDPTR right = parent->ptr[index2+1];
		T->ptr[index1] = merge_nodes(T->ptr[index1], T->ptr[index1 +1]);
		// parent->ptr[index2] = merge_nodes(parent->ptr[index2]
		int i;
		for(i=index1; i<T->cnt-1; i++){
			T->key[i] = T->key[i+1];
			T->ptr[i+1] = T->ptr[i+2];
		}
		
		if(marker == 0){
			marker= 1;
			T->key[T->cnt-1] = parent->key[index2];
			del_util(parent, parent->key[index2], index2, get_parent(main_tree, parent), main_tree);
			
		}else{
			marker = 0;
			T->cnt--;
		}
		
//		T->cnt--;
		
		
		
	}else if(index2>0){
		BDPTR left = parent->ptr[index2-1];
		T->ptr[index1] = merge_nodes(T->ptr[index1], T->ptr[index1 +1]);
		int i;
		for( i=index1; i>0; i--){
			T->key[i] = T->key[i-1];
			T->ptr[i+1] = T->ptr[i];
		}
		
		if(marker == 0){
			marker= 1;
			T->key[0] = parent->key[index2-1];
			del_util(parent, parent->key[index2-1], index2-1, get_parent(main_tree, parent), main_tree);
			
		}else{
			marker = 0;
			T->cnt--;
		}
//		if(underflow(T) and parent){
//			if(marker == 0){
//				marker = 1;
//				T->key[0] = parent->key[index2-1];
//			del_util(parent, parent->key[index2-1], index2-1, get_parent(main_tree, parent), main_tree);
//			}else{
//				marker = 0;
//			}
//			
//			
//		}
		
		
		
	}else if(index2 == -1) {
		T->ptr[index1] = merge_nodes(T->ptr[index1], T->ptr[index1 +1]);
		for(int i=index1;i<T->cnt-1;i++){
			T->key[i] = T->key[i+1];
			T->ptr[i+1]= T->ptr[i+2];
		}
		T->cnt--;
	}
}
//
//void NodeCombine(BDPTR &T,BDPTR &p,int index,int index1){
////	int flag1 = check_leaf_node(T);
//	int c;
//	c = p->key[index];
////	del(p, p->key[index]);
//	T->key[T->cnt++] = c;
//	T->ptr[T->cnt] = p->ptr[index+1]->ptr[0];
////	sort(T,T->cnt);
//	int i = T->cnt,j=0;
////	if(flag1)
////	while(i<T->cnt-1){
////		T->key[i] = T->key[i+1];
////		T->ptr[i] = T->ptr[i+1];
////	}
//	int a;
//	BDPTR b;
////	if(p->ptr[index1+1]){
//	BDPTR right = p->ptr[index1+1];
//	while(i<=2*d){											//..........
//		a = right->key[j];
//		b = right->ptr[j];
////		del_util(right,right->key[j],j,p);
//		T->key[i] = a;
//		T->ptr[i] = b;
//		i++;
//		j++;
//		T->cnt++;
//	}
//	
//	SortwithPTR(T,T->cnt);
//	
////	del_util(T,T->key[index1],index1,p);
//	
//	 i = p->cnt-1;
//	while(i>0){
//			p->key[i-1] = p->key[i]; //right_shift
//			p->ptr[i] = p->ptr[i+1];
//	//		t->ptr[left_index+1]->ptr[i] = NULL;
//			i--;
//		}
//	p->cnt--;	
////	del(T,T->key[index1],index1,p);	
//	//	// parent is root..
////	if(p->cnt <= d ){
////		p->ptr[index+1] = NULL;
////		p=p->ptr[index];
////	//	T=NULL;
////	//	p->ptr[index]=T;
////	}
////	else{
////		i=1;
////		while(i<p->cnt){
////			p->key[i] = p->key[i+1];
////			p->ptr[i] = p->ptr[i+1];
////		}
////		p->ptr[index+1] = NULL;
////	//	del(p,p->key[index]);
//		
//	}

//	else{
//		BDPTR left = p->ptr[index1 - 1];
//	}
//	
//	T->ptr[i] = t->ptr[index+1]->ptr[j];   // Todo : FREE the old node

int maxBD(BDPTR &X, BDPTR &y , BDPTR &y_p, int index1, int &y_index_1){			//(X->ptr[index1], y, y_index_1, y_p);
	
	y = X->ptr[index1];
	if(y==NULL)
	return -1;
	while(y->ptr[y->cnt]!=NULL){
		y_p = y;
		y = y->ptr[y->cnt];
	}
//	y_p->ptr[y_index1] = y;
	
//	D = del(D,D->key[D->cnt],0,NULL);
    if(!underflow(y)){
    	y_index_1 = y->cnt-1;
    	return(y->key[y->cnt-1]);
	}
	
	
	else{
		int temp_index = y->cnt-1;
	int number = y->key[y->cnt-1];
	BDPTR temp_y = y;
	BDPTR temp_y_p = y_p;
		y=X->ptr[index1+1];
		if(y==NULL)
	return -1;
	while(y->ptr[0]!=NULL){
		y_p = y;
		y = y->ptr[0];
	}
//	y_p->ptr[y_index1] = y;
	
//	D = del(D,D->key[D->cnt],0,NULL);
    if(!underflow(y)){
    	y_index_1 = 0;
    	return(y->key[0]);
	}
	if(!underflow(X->ptr[index1]) or !underflow(X->ptr[index1+1]))
	{y_p = temp_y_p;
	y= temp_y;
	y_index_1 = temp_index;
return number;}
else return -2;
	
	}
//	return -2;

	
}

int minBD(BDPTR &X, BDPTR &y , BDPTR &y_p, int index1, int &y_index_1){
	y = X;
	if(y==NULL)
	return -1;
	while(y->ptr[0]!=NULL)
	{
		y_p = y;
		y = y->ptr[0]; 
	}
	y_index_1 = 0;
	return (y->key[0]);
}

void del_util(BDPTR &X,int k,int index1,BDPTR p, BDPTR main_tree){
	int flag1=1;
    
    if(p == NULL){
    	cout<<" parent of "<<X->key[0]<<" is NULL!"<<"\n";
	}else{
		cout<<" parent and index of "<<X->key[0]<<" are "<<p->key[0]<<" "<<index1<<"\n";
	}

	//if element is found
	if(index1!=-1){
		flag1 = check_leaf_node(X); 
		//is leaf node
		if(flag1){
			cout<<"leaf node"<<"\n";
			if(underflow(X)){
					// check for KEY REDISTRIBUTION
					if(p){
						int index2 = get_index_in_parent(X,p);
						
					if(index2 == -1){
						cout<<"T not found in p"<<"\n";
						exit(0);
					}
						cout<<X->key[0]<<" has parent and is at index :"<<index2<<"\n";
						int f = checkKRdel(X,p,index2,index1,main_tree);
//						if(f == 1)  //for left to right
//						del_util(X,k,index1+1,p,main_tree);
//						//NODE combine
//						if(f == 2) //right to left
//						del_util(X,k,index1,p,main_tree);
						if(!f)
						{
							bool b = checkFULLKRdel(X,p,index2,index1,main_tree);
						
						if(!b){
			
						cout<<"node combine"<<X->key[0]<<"\n";
						NodeCombine(X,p,index2,index1, main_tree);
						
						}
					//	del_util(X,k,index1,p);
						}											// --- doubtful
				}
					//NODE combine if root is underflow
					else{
						for(int i = index1; i<X->cnt-1;i++)
						X->key[i] = X->key[i+1];
						X->cnt--;
					}
				}
			// T does not underflow	
			else{
			cout<<X->key[index1]<<" doesnot overflow\n";		
					for(int i = index1; i<X->cnt-1;i++)
						X->key[i] = X->key[i+1];
						X->cnt--;
				}	
		}
		//not leaf node
		else{
			BDPTR y , y_p;
						cout<<"not leaf node\n";
						int y_index_1 = 0;
						int temp = maxBD(X,y, y_p,index1, y_index_1);
						if (temp>=0){			
						X->key[index1] = temp;
						cout<<"temp ="<<temp;
						del_util(y,X->key[index1],y_index_1,y_p,main_tree);
					}
						else if(temp==-1){
							cout<<"tree is wrongly constructed";
							exit(0); 
						}else{
							cout<<X->key[0]<<"is at node combine\n";
						
							int index2 = get_index_in_parent(X,p);
							NodeCombine(X, p, index2, index1, main_tree);
							if(X->cnt<d){
					// check for KEY REDISTRIBUTION
					if(p){
					int index2 = get_index_in_parent(X,p);
						
					if(index2 == -1){
						cout<<"T not found in p"<<"\n";
						exit(0);
					}
						cout<<X->key[0]<<" has parent and is at index :"<<index2<<"\n";
						bool f = checkKRdel(X,p,index2,index1, main_tree, false);
//						if(f == 1)  //for left to right
//						del_util(X,k,index1+1,p,main_tree);
//						//NODE combine
//						if(f == 2) //right to left
//						del_util(X,k,index1,p,main_tree);
						//NODE combine
						if(!f)
						{
								bool b = checkFULLKRdel(X,p,index2,index1,main_tree);
						
						if(!b){

						NodeCombine(X,p,index2,index1, main_tree);
					//	del_util(X,k,index1,p);
						}	
					}
					}
					else{
						BDPTR y =X->ptr[index1] , y_p =X;
						int y_index_1;
						int temp = maxBD(X,y, y_p,index1, y_index_1);
						if (temp>=0){			
						X->key[index1] = temp;
						del_util(y,X->key[index1],y_index_1,y_p,main_tree);
					}
						else if(temp==-1){
							cout<<"tree is wrongly constructed";
							exit(0); 
						}else{
							
							int index2 = get_index_in_parent(X,p);
							NodeCombine(X, p, index2, index1, main_tree);
						}
					}
					
//					// flag2  = 0 -- means it is root element
//					else{
//						
//					}
			}
							
						}
			
//			else{
//				cout<<"index1 = "<<index1<<"\n";
//			BDPTR y =X->ptr[index1] , y_p =X;
//						int y_index_1;
//						int temp = maxBD(X,y, y_p,index1);
//						if (temp>=0){			
//						X->key[index1] = temp;
//						del_util(y,X->key[index1],y_index_1,y_p,main_tree);
//					}
//						else if(temp==-1){
//							cout<<"tree is wrongly constructed";
//							exit(0); 
//						}else{
//							// my charging got finished
//							//put now
//							int index2 = get_index_in_parent(X,p);
//							NodeCombine(X, p, index2, index1, main_tree);
//						}
//				
//			}
		}
	}
	//element is not found!!
	else{
		cout<<"THE ELEMENT WAS NOT FOUND -- TRY AGAIN!";
		exit(0);
	}
	
		cout<<"\nTree till now:\n"; 
		if(X)
	levelOrderPrint(X);
	
}

void del(BDPTR &T, int k){
	//,0,NULL
	BDPTR X = NULL, p=NULL;
	int index1;
	
	X = search(T,k,p,index1);
	
	del_util( X, k, index1, p, T);
	
}

int main(){
	int k;
	BDPTR T=NULL;
	int c;
	
//	cout<<"Enter d: ";
//	cin>>d;
// input 5 8 3 6 4 2 1 9 7 -1
// or 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 -1
// input 1 50 100 25 75 20 30 12 13 80 70 65 90 -1
//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 -1
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 40 50 60 70 90 100 110 120 123 125 130 140 145 150 -1
//235 253 362 745 856 896
 cout<<"Enter the elements to add: \n";
	while(1){
		cout<<"Enter value: "; cin>>k;
		if(k==-1)
		break;
		T = Add(T,k,0,NULL);
		cout<<"\n"<<"----------"<<"\n";
		//levelOrderPrint(T);
		cout<<"\n"<<"----------"<<"\n";
}

//int a[]= {5,8,3,6,4,2,1};
//int n = 7;
//	for(int i=0;i<n;i++){
//		cout<<"\n"<<"----------"<<"\n";
//		T = Add(T,a[i],0,NULL);
//	}
	// printing
	cout<<"\n";
	cout<<"\nINORDER :\n";
	if(T)
	inorder(T);
	cout<<"\nLEVEL ORDER :\n";
	if(T)
	levelOrderPrint(T);
	cout<<"END";
	// DELETION OF NODES
	cout<<"\n----------------\n";
	cout<<"Enter elements to delete : \n";
		while(1){
		cout<<"Enter value: "; cin>>k;
		if(k==-1)
		break;
		del(T,k);
		cout<<"DELETE "<<k<<" \n";
		cout<<"\n"<<"----------"<<"\n";
		levelOrderPrint(T);
		cout<<"\n"<<"----------"<<"\n";
	}
		//printing
	cout<<"\n";
	cout<<"\nINORDER :\n";
	if(T)
	inorder(T);
	cout<<"\nLEVEL ORDER :\n";
	if(T)
	levelOrderPrint(T);
	cout<<"END";


	return 0;
}
