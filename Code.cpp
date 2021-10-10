#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using namespace std;

struct node{
    int key;
    struct node* next;
};

struct Edge{
    int s;
    int d;
    int w;
};

struct node* pointer(struct node* head,int n){
    struct node* temp = head;
    while(n!=0){
        temp=temp->next;
        n--;
    }
    return temp;
}

void addnode(struct node** head, int key){
    struct node* x = (struct node*) malloc(sizeof(struct node));
    x->key=key;
    x->next=NULL;

    struct node* temp = *head;
    if(temp==NULL){
        *head=x;
        return;
    }
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=x;
    return;
}

void undirBFS(int N , int s){
    int i,j;
    int te=0,ce=0;

    // take adj. matrix from input
    int adj[N][N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> adj[i][j];
        }
    }

    // initial visit array as all false value
    bool visit[N];
    for(i=0;i<N;i++){
        visit[i]=false;
    }

    // distance array
    int dis[N];
    for(i=0;i<N;i++){
        dis[i]=0;
    }

    // initializing queue for BFS
    queue <int> Q;

    // BFS process with updating distances from source
    visit[s-1]=true;
    Q.push(s-1);

    while(!Q.empty()){
        s=Q.front();
        Q.pop();

        for(i=0;i<N;i++){
            if(adj[s][i]==1){
                if(visit[i]==false){
                    visit[i]=true;   // making visited node
                    te++;            // adding no. of tree edges
                    Q.push(i);       // push that node into queue
                    dis[i]=dis[s]+1; // updating the distance from source
                }
                else{
                    if(dis[s]==dis[i] || dis[i]==dis[s]+1){
                        adj[i][s]=0; // do not count double
                        ce++;  // distance of source should be less than that node
                    }
                }
            }
        }
    }

    // finding maxdistance from sorce
    int maxdis=0;
    for(i=0;i<N;i++){
        if(dis[i]>maxdis){
            maxdis=dis[i];
        }
    }

    // printing no. of nodes with i distance
    for(i=1;i<=maxdis;i++){
        int num=0;
        for(j=0;j<N;j++){
            if(dis[j]==i){
                num++;
            }
        }
        cout << num << " ";
    }

    //printing no. of tree edges and cross edges
    cout << "0 " << te << " " << ce << "\n";

    return;
}

void dirBFS(int N , int s){
    int i,j;
    int te=0,ce=0,fe=0,be=0;
    
    // take adj. matrix from input
    int adj[N][N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> adj[i][j];
        }
    }

    // initial visit array as all false value
    bool visit[N];
    for(i=0;i<N;i++){
        visit[i]=false;
    }

    // distance array
    int dis[N];
    for(i=0;i<N;i++){
        dis[i]=0;
    }

    // parent array
    int par[N];
    for(i=0;i<N;i++){
        par[i]=-1;
    }

    // initializing queue for BFS
    queue <int> Q;

    // BFS process with updating distances from source
    visit[s-1]=true;
    Q.push(s-1);

    while(!Q.empty()){
        s=Q.front();
        Q.pop();

        for(i=0;i<N;i++){
            if(adj[s][i]==1){
                if(visit[i]==false){
                    visit[i]=true;        // making visited node
                    te++;                 // adding no. of tree edges
                    Q.push(i);            // push that node into queue
                    par[i]=s;             // updating its parent node
                    dis[i]=dis[s]+1;      //updating the distance from source
                }
                else{
                    int a=s,b=i,c=dis[s],d=dis[i];
                    if(d>c){
                        ce++;
                    }
                    else if(c>d){       // check that it is back edge or not
                        while(c>d){
                            a=par[a]; 
                            c=dis[a];
                        }
                    }
                    if(a==b){
                        be++;
                    }
                    else{
                        ce++;
                    }
                }
            }
        }
    }

    // finding maxdistance from sorce
    int maxdis=0;
    for(i=0;i<N;i++){
        if(dis[i]>maxdis){
            maxdis=dis[i];
        }
    }

    // printing no. of nodes with i distance
    for(i=1;i<=maxdis;i++){
        int num=0;
        for(j=0;j<N;j++){
            if(dis[j]==i){
                num++;
            }
        }
        cout << num << " ";
    }

    //printing no. of tree edges and cross edges
    cout << "0" << te << " " << be << " " << fe << " " << ce << "\n";
    
    return;
}

void undirDFS(int N,int s){
    int i,j,t=0;
    int te=0,be=0;
    bool flag=true;

    // take adj matrix
    int adj[N][N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> adj[i][j];
        }
    }

    // colour of node
    char c[N];
    for(i=0;i<N;i++){
        c[i]='W';
    }

    // discover time
    int div[N];
    for(i=0;i<N;i++){
        div[i]=0;
    }

    // finish time
    int fin[N];
    for(i=0;i<N;i++){
        fin[i]=0;
    }

    // parent of node
    int par[N];
    for(i=0;i<N;i++){
        par[N]=-1;
    }
    
    // initializing stack
    stack <int> S;

    // add source node
    t++;
    div[s-1]=t;
    c[s-1]='G';
    S.push(s-1);

    while(!S.empty()){
        s=S.top();
        flag=true;

        for(i=1;i<N;i++){
            if(adj[s][i]==1){
                if(c[i]=='W'){
                    t++;
                    div[i]=t;
                    c[i]='G';
                    par[i]=s;
                    te++;
                    S.push(i);
                    flag=false;
                    break;
                }
            }
        }

        if(flag==true){
            t++;
            fin[s]=t;
            c[s]='B';
            S.pop();
        }
    }
    
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(div[i]<div[j] && fin[i]>fin[j] && adj[i][j]!=0 && div[i]!=div[j]-1){
                be++;
            }
        }
    }

    // printing finish time of source and tree and back edges
    cout << fin[s] << " " << te << " " << be << "\n";

    return;

}

void dirDFS(int N,int s){
    int i,j,t=0,sr=s;
    int te=0,be=0,fe=0,ce=0;
    bool flag=true;

    // take adj matrix
    int adj[N][N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> adj[i][j];
        }
    }

    // colour of node
    int visit[N];
    for(i=0;i<N;i++){
        visit[i]=0;
    }

    // discover time
    int div[N];
    for(i=0;i<N;i++){
        div[i]=0;
    }

    // finish time
    int fin[N];
    for(i=0;i<N;i++){
        fin[i]=0;
    }

    // parent of node
    int par[N];
    for(i=0;i<N;i++){
        par[N]=-1;
    }
    
    // initializing stack
    stack <int> S;

    // add source node
    t++;
    div[s-1]=t;
    visit[s-1]=1;
    S.push(s-1);

    while(!S.empty()){
        s=S.top();
        flag=true;

        for(i=1;i<N;i++){
            if(adj[s][i]==1){
                if(visit[i]==0){
                    t++;
                    div[i]=t;
                    visit[i]=1;
                    par[i]=s;
                    te++;
                    S.push(i);
                    flag=false;
                    break;
                }
                if(visit[i]==1){
                    be++;
                }
                if(visit[i]==2){
                    if(div[i]>div[s] && div[s]!=div[i]-1){
                        fe++;
                    }
                    else if(div[i]<div[s]){
                        ce++;
                    }
                }
            }
        }

        if(flag==true){
            t++;
            fin[s]=t;
            visit[s]=2;
            S.pop();
        }

    }

    

    // printing output
    cout << fin[s] << " ";
    cout << te << " " << be << " " << fe << " " << ce << "\n";

    return;
}

void topologicalsort(int N){

    int i,j,t=0,s;
    int fe,ce,be,te;
    bool flag=true;

    int adj[N][N];
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> adj[i][j];
        }
    }

    // indegree of nodes
    int indeg[N];
    for(i=0;i<N;i++){
        indeg[i]=0;
    }
    
    int par[N];

    // updating indegree of nodes
    for(j=0;j<N;j++){
        for(i=0;i<N;i++){
            if(adj[i][j]==1){
                indeg[j] += 1;
            }
        }
    }

    // take 0 indegree nodes
    set <int> Q;
    for(i=0;i<N;i++){
        if(indeg[i]==0){
            Q.insert(i);
        }
    }

    // colour of node
    char c[N];
    for(i=0;i<N;i++){
        c[i]='W';
    }

    int div[N],fin[N];
    s=*(Q.begin());
    j=1;    
    
    vector <int> sort;
    while(!Q.empty()){
        s=*(Q.begin());
        Q.erase(Q.begin());
        sort.push_back(s);

        // update all adj. vertex indegree and add to Q(if 0)
        for(i=0;i<N;i++){
            if(adj[s][i]==1){
                indeg[i] -= 1;
                if(indeg[i]==0){
                    Q.insert(i);
                    j++;
                }
            }
        }
    }

    if(j!=N){
        cout << "-1\n";
        return;
    }

    for(i=0;i<sort.size();i++){
            cout << sort[i]+1 << " ";
        }
    cout << "\n";
    return; 
}

void undirdijkstra(int N,int s){
    int i,j,a;

    // convert input into adj. list
    struct node* arr[N];
    for(i=0;i<N;i++){
        arr[i]=NULL;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> a;
            addnode(&arr[i],a);
        }
    }
    
    // parent array
    int par[N];
    for(i=0;i<N;i++){
        par[i]=-1;
    }

    // visit array to confirm sortest path
    bool visit[N];
    for(i=0;i<N;i++){
        visit[i]=false;
    }

    // distance vector and set all dis. 999999
    vector<int> dis;
    for(i=0;i<N;i++){
        dis.push_back(999999);
    }

    set<pair<int,int>> S;
    S.insert(make_pair(0,s-1));
    dis[s-1]=0;

    struct node* x;

    while(!S.empty()){
        pair<int,int> temp = *(S.begin());
        S.erase(S.begin());
        a=temp.second;
        visit[a]=true;
        for(i=0;i<N;i++){
            x=pointer(arr[a],i);
            if(x->key!=0 && x->key!=999999){
                if(par[i]==-1){
                    par[i]=a;
                }
                if(par[a]!=i){
                if(dis[i]>dis[a]+x->key){
                    if(visit[i]==true){
                        cout << "-1\n";
                        return;
                    }
                    if(dis[i]!=999999){
                        S.erase(S.find(make_pair(dis[i],i)));
                    }
                    dis[i]=dis[a]+x->key;
                    S.insert(make_pair(dis[i],i));
                }
                }
            }
        }
    }

    for(i=0;i<dis.size();i++){
        cout << dis[i] << " ";
    }
    cout << "\n";
    return;
}

void dirdijkstra(int N,int s){
    int i,j,a;

    // convert input into adj. list
    struct node* arr[N];
    for(i=0;i<N;i++){
        arr[i]=NULL;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> a;
            addnode(&arr[i],a);
        }
    }

    // visit array to confirm sortest path
    bool visit[N];
    for(i=0;i<N;i++){
        visit[i]=false;
    }

    // distance vector and set all dis. 999999
    int dis[N];
    for(i=0;i<N;i++){
        dis[i]=999999;
    }
    

    set<pair<int,int>> S;
    S.insert(make_pair(0,s-1));
    dis[s-1]=0;

    struct node* x;
    j=0;

    while(!S.empty()){
        pair<int,int> temp = *S.begin();
        S.erase(S.begin());
        a=temp.second;
        visit[a]=true;
        for(i=0;i<N;i++){
            x=pointer(arr[a],i);
            if(x->key!=0 && x->key!=999999){
                if(dis[i]>dis[a]+x->key){
                    if(visit[i]==true){
                        cout << "-1\n";
                        return;
                    }
                    if(dis[i]!=999999){
                        S.erase(S.find(make_pair(dis[i],i)));
                    }
                    dis[i]=dis[a]+x->key;
                    S.insert(make_pair(dis[i],i));
                }
            }
        }        
    }

    for(i=0;i<N;i++){
        cout << dis[i] << " ";
    }
    cout << "\n";
    return;
}

void undirbellman(int N,int s){
    int i,j,a,ne=0,nrp=0,nrm=0;
    int sr,d,w;

    struct node* x;

    // input as list
    struct node* arr[N];
    for(i=0;i<N;i++){
        arr[i]=NULL;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> a;
            addnode(&arr[i],a);
            if(a!=0 && a!=999999 && a!=-999999){
                ne++;
            }
        }
    }

    struct Edge E[ne];
    ne=0;
    
    // edge store in array
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            x=pointer(arr[i],j);
            if(x->key!=0 && x->key!=999999 && x->key!=-999999){
                E[ne].s=i;
                E[ne].d=j;
                E[ne].w=x->key;
                ne++;
            }
        }
    }

    // distances of nodes
    int dis[N];
    for(i=0;i<N;i++){
        dis[i]=999999;
    }

    // parent array
    int par[N];
    for(i=0;i<N;i++){
        par[i]=-1;
    }

    dis[s-1]=0;

    for(i=0;i<N;i++){
        a=0;
        for(j=0;j<ne;j++){
            sr=E[j].s;
            d=E[j].d;
            w=E[j].w;
            nrp++;
            if(dis[sr]!=999999 && dis[sr]!=-999999 && dis[sr]+w<dis[d] && (dis[sr]+w!=dis[d] || dis[sr]!=dis[d]+w)){
                dis[d]=dis[sr]+w;
                nrm++;
                a++;
            }
        }
        if(a==0){
            break;
        }
        else if(a>0 && i==N){
            cout << "-1\n";
            return;
        }
    }
    
    for(i=0;i<N;i++){
        cout << dis[i] << " ";
    }
    cout << nrp << " " << nrm << "\n";
    return;
}

void dirbellman(int N,int s){
    int i,j,a,ne=0,nrp=0,nrm=0;
    int sr,d,w;

    struct node* x;

    // input as list
    struct node* arr[N];
    for(i=0;i<N;i++){
        arr[i]=NULL;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cin >> a;
            addnode(&arr[i],a);
            if(a!=0 && a!=999999 && a!=-999999){
                ne++;
            }
        }
    }

    struct Edge E[ne];
    ne=0;
    
    // edge store in array
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            x=pointer(arr[i],j);
            if(x->key!=0 && x->key!=999999 && x->key!=-999999){
                E[ne].s=i;
                E[ne].d=j;
                E[ne].w=x->key;
                ne++;
            }
        }
    }

    // distances of nodes
    int dis[N];
    for(i=0;i<N;i++){
        dis[i]=999999;
    }

    // parent array
    int par[N];
    for(i=0;i<N;i++){
        par[i]=-1;
    }

    dis[s-1]=0;

    for(i=0;i<N;i++){
        a=0;
        for(j=0;j<ne;j++){
            sr=E[j].s;
            d=E[j].d;
            w=E[j].w;
            nrp++;
            if(dis[sr]!=999999 && dis[sr]!=-999999 && dis[sr]+w<dis[d]){
                dis[d]=dis[sr]+w;
                nrm++;
                a++;
            }
        }
        if(a==0){
            break;
        }
        else if(a>0 && i==N){
            cout << "-1\n";
            return;
        }
    }
    
    for(i=0;i<N;i++){
        cout << dis[i] << " ";
    }
    cout << nrp << " " << nrm << "\n";
    return;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int Q,N,D,s;
        cin >> Q;
        if(Q==1){
            cin >> N >> D >> s;
            if(D==0){
                undirBFS(N,s);
            }
            else if(D==1){
                dirBFS(N,s);
            }
        }
        else if(Q==2){
            cin >> N >> D >> s;
            if(D==0){
                undirDFS(N,s);
            }
            else if(D==1){
                dirDFS(N,s);
            }
        }
        else if(Q==3){
            cin >> N ;
            topologicalsort(N);
        }
        else if(Q==4){
            cin >> N >> D >> s;
            if(D==0){
                undirdijkstra(N,s);
            }
            else if(D==1){
                dirdijkstra(N,s);
            }
        }
        else if(Q==5){
            cin >> N >> D >> s;
            if(D==0){
                undirbellman(N,s);
            }
            else if(D==1){
                dirbellman(N,s);
            }
        }
    }
    return 0;
}