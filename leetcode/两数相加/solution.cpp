#include<iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int v):val(v),next(NULL) {}
};

class Solution {
public:
	ListNode*  addTwoNumbers1(ListNode* l1,ListNode* l2) {
		ListNode* root = new ListNode(0);
		ListNode* cur=root,*tmp;
		int carry=0,sum;
		while(l1&&l2) {
			sum=l1->val+l2->val+carry;
			carry=sum/10;
			tmp=new ListNode(sum%10);
			cur->next=tmp;
			cur=tmp;
			l1=l1->next;
			l2=l2->next;
		}

		while(l1) {
			sum=l1->val+carry;
			carry=sum/10;
			tmp=new ListNode(sum%10);
			cur->next=tmp;
			cur=tmp;
			l1=l1->next;
		}
		while(l2) {
			sum=l2->val+carry;
			carry=sum/10;
			tmp=new ListNode(sum%10);
			cur->next=tmp;
			cur=tmp;
			l2=l2->next;
		}

		if(carry) {
			tmp=new ListNode(1);
			cur->next=tmp;
			cur=tmp;
		}
		return root->next;
	}
    
    ListNode* addTwoNumbers2(ListNode* l1,ListNode* l2){
        ListNode* root=new ListNode(0),*tmp;
        ListNode* cur=root;
        int carry=0,sum,lval,rval;
        
        //只要l1,l2,carry有一个不为0，就进行下面的步骤
        while(l1||l2||carry){
            lval=l1?l1->val:0;
            rval=l2?l2->val:0;
            sum=lval+rval+carry;
            carry=sum/10;
            tmp=new ListNode(sum%10);
            cur->next=tmp;
            cur=tmp;
            if(l1)l1=l1->next;
            if(l2)l2=l2->next;
        }
        return root->next;
    }
    
    //利用原数组节省空间
    ListNode* addTwoNumbers3(ListNode* l1,ListNode* l2){
        ListNode* root=new ListNode(0),*tmp;
        ListNode* cur=root;
        root->next=l1;
        
        int carry=0,sum,lval,rval;
        
        while(l1||l2||carry){
            lval=l1?l1->val:0;
            rval=l2?l2->val:0;
            sum=lval+rval+carry;
            carry=sum/10;
            if(cur->next){
                cur->next->val=sum%10;
            }else{
                tmp=new ListNode(sum%10);
                cur->next=tmp;
            }
            cur=cur->next;
            if(l1)l1=l1->next;
            if(l2)l2=l2->next;
        }
        return root->next;
    }
};

ListNode* makeList(int arr[],int len) {
	ListNode* root = new ListNode(arr[0]);
	ListNode* cur=root,*tmp;
	for(int i=1; i<len; ++i) {
		tmp=new ListNode(arr[i]);
		cur->next=tmp;
		cur=tmp;
	}
	return root;
}

void printList(ListNode* l) {
	while(l) {
		cout<<l->val;
		if(l->next)cout<<" ";
		else cout<<endl;
		l=l->next;
	}
}

int main() {
	Solution solution;
	int arr1[]= {2,4,3};
	int arr2[]= {5,6,4};
	ListNode* l1 = makeList(arr1,3);
	ListNode* l2 = makeList(arr2,3);

	ListNode* res=solution.addTwoNumbers3(l1,l2);

	printList(res);
	return 0;
}
