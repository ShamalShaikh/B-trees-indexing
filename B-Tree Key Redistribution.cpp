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

int get_index_in_parent(BDPTR T,BDPTR t){
	for(int i=0;i<t->cnt +1;i++){
		if(t->ptr[i]==T)
		return i;
	}
	return -1;
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
			t->key[index] =t->ptr[index]->key[T->cnt];
		//	T->key[T->cnt] = 0;
		}

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
		for(int i=0;i<T->cnt;++i)
		{
			if(T->ptr[i]!=NULL)
			flag1=0;
		}
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
			cout<<"T not found in t"<<endl;
			exit(0);
		}
			cout<<T->key[0]<<" has parent and is at index :"<<index<<endl;
			checkKeyRedistribution(T,t,index);
		}
		
		if(Overflow(T))							
		{
				int median;
			median = findMedian(T,k);
			
//			cout<<"******"<<median<<"\n";
			
//			cout<<isNull(T->ptr[0])<<endl;
//			cout<<isNull(T->ptr[1])<<endl;
//			cout<<isNull(T->ptr[2])<<endl;
			BDPTR temp = createNewNode(T);
//			cout<<isNull(temp->ptr[0])<<endl;
//			cout<<isNull(temp->ptr[1])<<endl;
//			cout<<isNull(temp->ptr[2])<<endl;
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
//			cout<<endl;
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

//bool BDsearch(BDPTR T,int k){
//	if(T==NULL)
//	return false;
//	else{
//		for(int i=0;i<T->cnt;++i)
//		{
//			if(T->key[i]==k)
//			return true;
//			else
//			if(T->key[i]>k)
//			return BDsearch(T->cptr[i],k);
//		}
//		return BDsearch(T->cptr[T->cnt],k);
//	}
//}
//
//BDPTR BDdelete(BDPTR T,int k){
//	
//	if(BDsearch(T,k)){
//		
//	}
//	else{
//		cout<<"THE ELEMENT WAS NOT FOUND -- TRY AGAIN!";
//	}
//}


int main(){
	int k;
	BDPTR T=NULL;
	
//	cout<<"Enter d: ";
//	cin>>d;
// input 5 8 3 6 4 2 1 9 7 -1
// or 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 -1
// input 1 50 100 25 75 20 30 12 13 80 70 65 90 -1
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
	
	return 0;
}
