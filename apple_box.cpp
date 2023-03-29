#include<iostream>
#include<vector>
using namespace std;

// part A

class Size{
    private:
        int *a, *s, len;
        void mergeSort(int, int);
        void merge(int, int);
        int IsLarge(int i, int j){
            if(a[i]>a[j]) return 1;
            else return -1;
        }
    public:
        Size(){
            cout<<"Enter the total number of apple: ";
            cin>>len;
            a = new int[len];
            s = new int[len];
            cout<<"Enter size of "<<len<<" apples"<<endl;
            for(int i=0; i<len; i++){
                cin>>a[i];
                s[i]=i;
            }
        }
        void mSort(){
            mergeSort(0,len-1);
        }
        void print(){
            cout<<"Apple: ";
            for(int i=0; i<len; i++){
                cout<<a[s[i]]<<" ";
            }cout<<endl;
            cout<<"Size: ";
            for(int i=0; i<len; i++){
                cout<<s[i]<<" ";
            }cout<<endl;
        }
        vector<int> SortedApple(){
            vector<int> temp;
            for(int i=0; i<len; i++){
                temp.push_back(a[s[i]]);
            }
            return temp;
        }
};

void Size::merge(int l, int r){

    int mid =l+(r-l)/2;
    int len1 = mid-l+1;
    int len2 = r-mid;

    int *first = new int[len1];
    int *second = new int [len2];

    int k=l;
    for(int i=0; i<len1;i++){
        first[i]=s[k++];
    }
    k=mid+1;
    for(int i=0; i<len2; i++){
        second[i]=s[k++];
    }
    int index1 = 0;
    int index2 = 0;
    k=l;

    while(index1<len1 && index2<len2){
        if(IsLarge(first[index1],second[index2])==-1){
            s[k++] = first[index1++];
        }else{
            s[k++] = second[index2++];
        }
    }
    while(index1 < len1){
        s[k++] = first[index1++];
    }
    while(index2 < len2){
        s[k++] = second[index2++];
    }
}

void Size::mergeSort(int l, int r){
    if(l>=r){ return ; }

    int mid= l+(r-l)/2;
    mergeSort(l, mid);
    mergeSort(mid+1, r);

    merge(l, r);
}

// part B

class Match{
    private:
        int *a, *b, *m, len;
        void swap(int*, int*);
        int partition(int, int);
        void quickSort(int, int);
    public:
        Match(vector<int>ap){
            len=ap.size();
            a=new int[len];
            b=new int[len];
            m=new int[len];
            cout<<"Enter size of "<<len<<" boxes"<<endl;
            for(int i=0; i<len; i++){
                a[i]=ap[i];
                m[i]=i;
                cin>>b[i];
            }  
        }
        void printArray();
        void qSort(){
            quickSort(0,len-1);
        }
        int TightFit(int i, int j){
            if(a[i]==b[j])
		        return 0;
	        else if(a[i]<b[j])
		        return 1;
	        else
		        return -1;
        }
};

void Match::swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int Match::partition(int low, int high) {

    int i = (low-1);

    for (int j = low; j < high; j++) {
        if (TightFit(high,j)==(-1)) {
            i++;
            swap(&m[i], &m[j]);
            swap(&b[i],&b[j]);
        }
    }
    swap(&m[i+1], &m[high]);
    swap(&b[i+1],&b[high]);
    return high--;
}

void Match::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void Match::printArray() {
    cout<<"Box: ";
    for (int i=0; i<len; i++)
        cout << b[i] << " ";
    cout << endl;
    cout<<"Match: ";
    for(int i=0; i<len; i++)
        cout<<m[i]<<" ";
    cout<<endl;
}

int main(){

    cout<<"Part A\n";
    Size a;
    a.mSort();
    cout<<"After merge Sort \n";
    a.print();
    cout<<"\nPart B\n";
    vector<int>apple=a.SortedApple();
    Match b=apple;
    b.qSort();
    cout<<"After matching \n";
    b.printArray();

    return 0;
}