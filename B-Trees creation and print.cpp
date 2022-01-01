#include<bits/stdc++.h>
using namespace std;
#define d 1

typedef struct bdnode{
	int cnt;
	int key[2*d +3];
	bdnode *ptr[2*d+1];
//	int *key;
//	int **ptr;
}*BDPTR;


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
					cout<<temp->key[i];
					if (temp->ptr[i])
					q.push(temp->ptr[i]);
				}
//				cout<<"#####"<<"\n";
				
				if (temp->ptr[temp->cnt])
				q.push(temp->ptr[temp->cnt]);
				cout<<" ";
			}
		}
}
//construct Bd-Tree
bool Overflow(BDPTR D){
	if(D->cnt > 2*d)
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
	for(int i=0,j=(T->cnt/2)+1;j<(T->cnt);++i,++j)
	{
		temp->key[i] = T->key[j];
	}
	
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
		cout<<"Median_index"<<MedianIndex<<endl<<T->key[0]<<" " <<t->key[0]<<" "<<temp->key[0]<<endl;
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


BDPTR Add(BDPTR &T,int k,int flag2,BDPTR t){
	int flag1=1;
	if(T==NULL){
	T= new bdnode;
	for(int i=0;i<2*d+1;++i)
	T->ptr[i]=NULL;
	T->cnt = 0;
	T->key[T->cnt++] = k;	
	return T;
	}
	else{
		for(int i=0;i<T->cnt;++i)
		{
			if(T->ptr[i]!=NULL)
			flag1=0;
		}
		//if leaf node
		if(flag1){
			T->key[T->cnt++] = k;
//			for(int p= 0;p<T->cnt;p++){
//				cout<<T->key[p];
//			}
//			cout<<"\n";
			// OVERFLOW CONDITION
			if(Overflow(T)){							
			int median;
			median = findMedian(T,k);
			cout<<"******"<<median<<"\n";
			BDPTR temp = createNewNode(T);
			cout<<"******"<<"\n";
			for(int p= 0;p<temp->cnt;p++){
				cout<<temp->key[p];
			}
			cout<<"\n";
			for(int p= 0;p<T->cnt;p++){
				cout<<T->key[p];
			}
			for(int i=(T->cnt/2);i<T->cnt;++i){
				T->key[i] = 0;
				T->ptr[i+1]= NULL;
			}
			T->cnt = T->cnt/2;
			for(int p= 0;p<T->cnt;p++){
				cout<<T->key[p];
			}
			cout<<"******"<<"\n";
			//if parent node is not present
			if(flag2 == 0){
				//createnewNode();
				BDPTR t = new bdnode;
				for(int i=0;i<2*d+1;++i)
				t->ptr[i]=NULL;
				t->cnt = 0;
				t->key[t->cnt++] = median;
				cout<<"******"<<"\n";
				T = adjust(t,T,temp,median);
				 
				for(int p= 0;p<T->cnt;p++){
				cout<<T->key[p];
			}
				cout<<T->ptr[0]->key[0]<<" "<<T->ptr[1]->key[0]<<"\n";
				
				cout<<"******"<<"\n";
			}
			else{ //parent present
				
				t->key[t->cnt++] = median;
				SortwithPTR(t,t->cnt);
				if(!Overflow(t))
				
					for(int p= 0;p<t->cnt;p++){
				cout<<t->key[p];
			}
			cout<<endl;
			for(int p= 0;p<T->cnt;p++){
				cout<<T->key[p];
			}
			cout<<t->ptr[0]->key[0];
//				cout<<t->ptr[1]->key[0];
				BDPTR z = adjust(t,T,temp,median); //to adjust pointers 
				cout<<z->key[0]<< " "<<z->key[1]<<"\n";
				cout<<z->ptr[0]->key[0]<< " "<<z->ptr[1]->key[0]<<"\n";
			}
					
		}
		// NODE STILL NOT FILLED
		else{
			sort(T,T->cnt);
		}
	
			
		}
		//not a leaf node
		else{
			int index = getIndex(T,k);
			T->ptr[index] = Add(T->ptr[index], k,1,T);
		
	}
}
	cout<<"\nTree till now:\n"; 
	levelOrderPrint(T);
	return T;
}




int main(){
	int k;
	BDPTR T=NULL;
	
//	cout<<"Enter d: ";
//	cin>>d;
// input 5 8 3 6 4 2 1 9 7 -1
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
	// printing
	cout<<"\n";
	inorder(T);
	cout<<"\nLEVEL ORDER :\n";
	
	levelOrderPrint(T);
	cout<<"END";
	
	return 0;
}
