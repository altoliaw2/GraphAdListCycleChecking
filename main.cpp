#include <algorithm>
#include <iostream>

struct Vet{
    public: char c_Name;
    public: Vet* clsp_Ptr;
};

struct AdList{
    public: Vet** cl2p_Ptr;
    public: char* cp_Name;
    public: int i_Size;

    public: AdList(char* cp_Name, int i_Size){
        cl2p_Ptr= new Vet*[i_Size];
        std::fill(cl2p_Ptr, cl2p_Ptr+ i_Size, nullptr);
        this->cp_Name = cp_Name;
        this->i_Size = i_Size;
    }

    public: bool fn_InsVet(char c_NameA, char c_NameB){
        int i_Ind = -1;
        for(int i_Ct= 0; i_Ct < i_Size; i_Ct++){
            if(c_NameA == cp_Name[i_Ct]){
                i_Ind = i_Ct;
                break;
            }
        }
        if(i_Ind == -1){
            return false;
        }

        Vet* o_Ele  = new Vet();
        o_Ele->c_Name = c_NameB;
        o_Ele->clsp_Ptr = cl2p_Ptr[i_Ind];
        cl2p_Ptr[i_Ind] = o_Ele;
    }

    public: ~AdList(){
        for(int i_Ct =0; i_Ct< i_Size; i_Ct++){
            for(Vet* o_Ele = cl2p_Ptr[i_Ct];
                o_Ele != nullptr;){
                Vet* o_Ele2  = o_Ele->clsp_Ptr;
                delete o_Ele;
                o_Ele = o_Ele2;
            }
        }
        delete [] cl2p_Ptr;
    }

    public: bool fn_isCyclic(){
        bool* bp_Visited = new bool[i_Size];
        bool* bp_RecStack = new bool[i_Size];
        std::fill(bp_Visited, bp_Visited+ i_Size, false);
        std::fill(bp_RecStack, bp_RecStack+ i_Size, false);

        for(int i_Ct = 0; i_Ct < i_Size; i_Ct++){
            if (fn_IsCyclic(i_Ct, bp_Visited, bp_RecStack)){
                return true;
            }
        }

        delete [] bp_Visited;
        delete [] bp_RecStack;
        return false;
    }

    private:bool fn_IsCyclic(int i_Ind, bool* bp_Visited,
                             bool* bp_RecStack){

        if(bp_Visited[i_Ind] == false){
            bp_Visited[i_Ind] = true;
            bp_RecStack[i_Ind] = true;

            for(Vet* op_Tmp= cl2p_Ptr[i_Ind]; op_Tmp!= nullptr;
                op_Tmp= op_Tmp->clsp_Ptr){

                int i_Tmp = fn_GetIndex(op_Tmp->c_Name);
                if ( !bp_Visited[i_Tmp] &&
                    fn_IsCyclic(i_Tmp, bp_Visited, bp_RecStack)
                    ){
                    return true;
                }
                else if (bp_RecStack[i_Tmp]){
                    return true;
                }
            }
        }
        bp_RecStack[i_Ind] = false;
        return false;
    }

    private: int fn_GetIndex(char c_Name){
        int i_Ind = -1;
        for(int i_Ct =0; i_Ct < i_Size; i_Ct++){
                if(cp_Name[i_Ct] == c_Name){
                    i_Ind= i_Ct;
                    break;
                }
        }
        return i_Ind;
    }
};

int main(){
    char c_Arr[] = {'1', '2', '3', '4'};
    int i_Size  = sizeof(c_Arr)/sizeof(char);
    AdList o_List = AdList(c_Arr, i_Size);

    o_List.fn_InsVet('1', '2');
    o_List.fn_InsVet('2', '3');
    o_List.fn_InsVet('3', '4');
    o_List.fn_InsVet('3', '1');

    std::cout<< (o_List.fn_isCyclic() == true ? "TRUE" : "FALSE");
    return 0;
}
