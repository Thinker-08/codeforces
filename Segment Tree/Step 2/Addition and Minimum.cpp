#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL)
#define int long long
using namespace std;
#define vi vector<int>
#define vvl vector<vector<int>>
#define vl vector<int>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define newline cout<<'\n'
const int N=1e5;
int tree[4*N];
int arr[N];
int lazy[4*N];
void build(int node,int st,int en)
{
    if(st==en)
    {
        tree[node]=arr[st];
        return;
    }
    else
    {
        int mid=(st+en)/2;
        build(2*node,st,mid);
        build(2*node+1,mid+1,en);
        tree[node]=tree[2*node]+tree[2*node+1];
    }
}
void rangeUpdate(int node,int low,int high, int l,int r,int val)
{
    if(lazy[node]!=0)
    {
        tree[node]+=lazy[node];
        if(low!=high)
        {
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }    
        lazy[node]=0;
    }
    if(r<low or l>high or low>high)
        return;
    if(low>=l and high<=r)
    {
        tree[node]+=val;
        if(low!=high)
        {
            lazy[2*node]+=val;
            lazy[2*node+1]+=val;
        }
        return;
    }
    int mid = (low+high)>>1;
    rangeUpdate(2*node,low,mid,l,r,val);
    rangeUpdate(2*node+1,mid+1,high,l,r,val);
    tree[node]=min(tree[2*node],tree[2*node+1]);
}
 
int querySumLazy(int node,int low,int high,int l,int r)
{
    if(lazy[node]!=0)
    {
        tree[node]+=lazy[node];
        if(low!=high)
        {
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node]=0;
    }    
    if(r<low or l>high or low>high)
        return INT_MAX;
    if(low>=l and high<=r)
        return tree[node];
    int mid=(low+high)>>1;
    return min(querySumLazy(2*node,low,mid,l,r),querySumLazy(2*node+1,mid+1,high,l,r));
}
int32_t main()
{
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1)
        {
            int d;
            cin>>d;
            rangeUpdate(1,0,n-1,b,c-1,d);
        }
        else
        {
            cout<<(querySumLazy(1,0,n-1,b,c-1));
            newline;
        }
    }
}