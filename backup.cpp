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

BDPTR Add(BDPTR &T,int k,int flag2,BDPTR t);
BDPTR del(BDPTR &T,int k,int flag2,BDPTR t);

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
	if(D->cnt<= 2*d)
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

int findMedian(BDPTR &D,int k){
	sort(D,D->cnt);
//	sortwithPTR(D,D->cnt);
	return D->key[D->cnt/2];
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

int get_index_in_parent(BDPTR T,BDPTR &t){
	for(int i=0;i<t->cnt +1;i++){
		if(t->ptr[i]==T)
		return i;
	}
	return -1;
}

void left_to_right(BDPTR &T,BDPTR &t,int left_index){
			//ADD in next sibling
		// del(T,T->key[T->cnt],1,t);
			int i=t->ptr[left_index+1]->cnt;
		while(i>0){
			t->ptr[left_index+1]->key[i] = t->ptr[left_index+1]->key[i-1];
			t->ptr[left_index+1]->ptr[i+1] = t->ptr[left_index+1]->ptr[i];
	//		t->ptr[left_index+1]->ptr[i] = NULL;
			i--;
		}
		t->ptr[left_index+1]->ptr[i+1] = t->ptr[left_index+1]->ptr[i];
		t->ptr[left_index+1]->cnt++;
			t->ptr[left_index+1]->key[0] = t->key[left_index] ;
			t->ptr[left_index+1]->ptr[0] = t->ptr[left_index]->ptr[T->cnt];
	//		t->ptr[left_index+1]->ptr[i]=NULL;
			T->cnt--;
			t->key[left_index] =t->ptr[left_index]->key[T->cnt];
		//	T->key[T->cnt] = 0;
		return;
}
void right_to_left(BDPTR &T,BDPTR &t,int left_index){
		cout<<T->key[0]<<" came here"<<endl;
		//ADD in previous sibling
		t->ptr[left_index-1]->key[t->ptr[left_index-1]->cnt++]= t->key[left_index-1];
		t->ptr[left_index-1]->ptr[t->ptr[left_index-1]->cnt]= t->ptr[left_index]->ptr[0];
		t->key[left_index-1] = t->ptr[left_index]->key[0];
		T->cnt--;
	//	del(T,T->key[0],1,t);
		int i=1;
		while(i<=T->cnt){
			T->key[i-1] = T->key[i];
			T->ptr[i-1] = T->ptr[i];
			i++;
		}
		T->ptr[i-1] = T->ptr[i];
		return;
}

bool checkKRdel(BDPTR &T,BDPTR &t,int index){
	if(index>0)
	if(t->ptr[index-1])
	if(t->ptr[index-1]->cnt<=d){}
	else{
		left_to_right(T,t,index);
		return true;
	}
	
	if(index<=t->cnt)
		if(t->ptr[index+1])
		if(t->ptr[index+1]->cnt<=d){
			return false;
		}
		else{
			right_to_left(T,t,index);
			return true;
		}	
}

void checkKeyRedistribution(BDPTR &T,BDPTR &t,int index){
	sort(T,T->cnt);
	
	if(index>0)
	if(t->ptr[index-1])
	if(t->ptr[index-1]->cnt>=2*d){}
	else{
		cout<<T->key[0]<<" came here"<<endl;
		//ADD in previous sibling
		t->ptr[index-1]->key[t->ptr[index-1]->cnt++]= t->key[index-1];
		t->ptr[index-1]->ptr[t->ptr[index-1]->cnt]= t->ptr[index]->ptr[0];
		t->key[index-1] = t->ptr[index]->key[0];
		T->cnt--;
	//	del(T,T->key[0],1,t);
		int i=1;
		while(i<=T->cnt){
			T->key[i-1] = T->key[i];
			T->ptr[i-1] = T->ptr[i];
			i++;
		
		}
		T->ptr[i-1] = T->ptr[i];
		return;
	}
		if(index<=t->cnt)
		if(t->ptr[index+1])
		if(t->ptr[index+1]->cnt>=2*d){
			return;
		}
		else{
			//ADD in next sibling
			int i=t->ptr[index+1]->cnt;
		while(i>0){
			t->ptr[index+1]->key[i] = t->ptr[index+1]->key[i-1];
			t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
	//		t->ptr[index+1]->ptr[i] = NULL;
			i--;
		}
		t->ptr[index+1]->ptr[i+1] = t->ptr[index+1]->ptr[i];
		t->ptr[index+1]->cnt++;
			t->ptr[index+1]->key[0] = t->key[index] ;
			t->ptr[index+1]->ptr[0] = t->ptr[index]->ptr[T->cnt];
	//		t->ptr[index+1]->ptr[i]=NULL;
			T->cnt--;
		// del(T,T->key[T->cnt],1,t);
			t->key[index] =t->ptr[index]->key[T->cnt];
		//	T->key[T->cnt] = 0;
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


int check_leaf_node(BDPTR T){
		int flag1 = 1;
		for(int i=0;i<T->cnt;++i)
		{
			if(T->ptr[i]!=NULL)
			flag1=0;
		}
		return flag1;
}

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
//			for(int p= 0;p<T->cnt;p++){
//				cout<<T->key[p];
//			}
//			cout<<"\n";
			// OVERFLOW CONDITION
			
	
			
		}
		//not a leaf node
		else{
			 index = getIndex(T,k);
			BDPTR x = Add(T->ptr[index], k,1,T);
			// T->ptr[index] = Add(T->ptr[index], k,1,T);
	}
	
	if(Overflow(T)){
		
		// check for KEY REDISTRIBUTION
		if((flag2==1)){
			int index = get_index_in_parent(T,t);
		if(index == -1){
			cout<<"T not found in t"<<"\n";
			exit(0);
		}
			cout<<T->key[0]<<" has parent and is at index :"<<index<<"\n";
			checkKeyRedistribution(T,t,index);
		}
		
		if(Overflow(T))							
		{
				int median;
			median = findMedian(T,k);
			
//			cout<<"******"<<median<<"\n";
			
//			cout<<isNull(T->ptr[0])<<"\n";
//			cout<<isNull(T->ptr[1])<<"\n";
//			cout<<isNull(T->ptr[2])<<"\n";
			BDPTR temp = createNewNode(T);
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
			for(int i=(T->cnt/2);i<T->cnt;++i){
				T->key[i] = 0;
//				T->ptr[i+1]= NULL;
			}
			T->cnt = T->cnt/2;
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
			continue;
			}
		}
		parent = X;
		X =  X->ptr[X->cnt];
	}
return X;
}

void NodeCombine(BDPTR T,BDPTR t,int index){
	int i = T->cnt,j=0;
	while(i<2*d){
		T->key[i] = t->ptr[index+1]->key[j];
		T->ptr[i] = t->ptr[index+1]->ptr[j];
		del(t->ptr[index+1],t->ptr[index+1]->key[j],1,t);
		j++;
	}
	T->ptr[i] = t->ptr[index+1]->ptr[j];   // Todo : FREE the old node
}
int maxBD(BDPTR D){
	while(D->ptr[D->cnt]!=NULL){
		D = D->ptr[D->cnt];
	}
	D = del(D,D->key[D->cnt],0,NULL);
	return(D->key[D->cnt]);
}
BDPTR del(BDPTR &T,int k,int flag2,BDPTR p){
	BDPTR X = T;
	int flag1 = 1;
	int index1; 
    X = search(X,k,p,index1);
    
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
						bool f = checkKRdel(X,p,index2);
						//NODE combine
						if(!f)
						{
						int index2 = get_index_in_parent(X,p);
						NodeCombine(X,p,index2);
						}											// --- doubtful
				}
					//NODE combine if root is underflow
//					else{
//						int index2 = get_index_in_parent(X,p);
//						NodeCombine(X,p,index2);
//					}
				}
			// T does not underflow	
			else{		int r = X->key[index1];
						X->key[index1] = 0;
						while(index1<X->cnt){
							X->key[index1]  = X->key[index1+1];
							
						//	T->ptr[index1]  = T->ptr[index1+1];
						}
						X->cnt--;
						return X;
				}	
		}
		//not leaf node
		else{
			if(underflow(X)){
					// check for KEY REDISTRIBUTION
					if((flag2==1)){
						int index2 = get_index_in_parent(X,p);
					if(index2 == -1){
						cout<<"T not found in p"<<"\n";
						exit(0);
					}
						cout<<X->key[0]<<" has parent and is at index :"<<index2<<"\n";
						checkKeyRedistribution(X,p,index2);
					}
					
//					// flag2  = 0 -- means it is root element
//					else{
//						
//					}
			}
			else{
				T->key[index1] = maxBD(T->ptr[index1]);
				del(T,maxBD(T->ptr[index1]),1,p);
			}
		}
	}
	//element is not found!!
	else{
		cout<<"THE ELEMENT WAS NOT FOUND -- TRY AGAIN!";
		return 0;
	}
	T=X;
		cout<<"\nTree till now:\n"; 
		if(T)
	levelOrderPrint(T);
	return T;
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
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 40 50 60 70 90 100 110 120 123 125 130 140 145 150 235 253 362 745 856 896
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
		T = del(T,k,0,NULL);
		cout<<"DELETE "<<k<<" \n";
		cout<<"\n"<<"----------"<<"\n";
		//levelOrderPrint(T);
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

