#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement);


LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this=(LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode=NULL;
    }
    //LinkedList* this= NULL;

    return this;
}


int ll_len(LinkedList* this)//devuelve el tamaño
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux=this->size;
    }
    return returnAux;
}



static Node* getNode(LinkedList* this, int nodeIndex)//sacar un lugar
{
    //int i;
    Node* pNode=NULL;
    if(this != NULL && nodeIndex>=0 && nodeIndex < ll_len(this))
    {
        pNode= this->pFirstNode;
        while(nodeIndex>0)
        {
            pNode=pNode->pNextNode;
            nodeIndex--;
        }
        /* for(i=0;i<nodeIndex;i++)
         {
             pNode=pNode->pNextNode;
             if(i==nodeIndex)
             {pNode=pNode->pNextNode;}
         }*/
    }
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}



 //Agrega y enlaza un nuevo nodo a la lista
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nuevoNode=NULL;

    if(this!=NULL&& nodeIndex>=0 && nodeIndex <= ll_len(this))
    {
        nuevoNode=(Node*) malloc(sizeof(Node));

        if(nuevoNode!= NULL)
        {
            nuevoNode->pElement=pElement;

            if(nodeIndex==0)
            {
                nuevoNode->pNextNode=this->pFirstNode;
                this->pFirstNode=nuevoNode;
            }
            else
            {
                nuevoNode->pNextNode= getNode(this,nodeIndex);
                (getNode(this,nodeIndex-1))->pNextNode=nuevoNode;
            }

            this->size++;
            returnAux=0;
        }

    }
    return returnAux;
}


 //Permite realizar el test de la funcion addNode la cual es privada
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}



 //Agrega un elemento a la lista
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        if(addNode(this,ll_len(this),pElement)==0)
        {
            returnAux=0;
        }

    }
    return returnAux;
}


 //Permite realizar el test de la funcion addNode la cual es privada
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxiNode=NULL;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        auxiNode=getNode(this,index);
        if(auxiNode != NULL)
        {
            returnAux=auxiNode->pElement;
        }
    }
    return returnAux;
}


 //Modifica un elemento de la lista
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxiNode=NULL;
    if(this != NULL && index >=0 && index < ll_len(this))
    {
        auxiNode=getNode(this,index);
        if(auxiNode!=NULL)
        {
            auxiNode->pElement=pElement;
            returnAux=0;
        }

    }
    return returnAux;
}



 //Elimina UN elemento de la lista
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxiNode=NULL;
    Node* preNode=NULL;

    if(this!=NULL && index >=0 && index < ll_len(this))
    {
        auxiNode=getNode(this,index);

        if(auxiNode!= NULL)
        {
            if(index==0)
            {
                this->pFirstNode=auxiNode->pNextNode;
            }
            else
            {
                preNode= getNode(this,index-1);
                if(preNode!=NULL)
                {
                    preNode->pNextNode=auxiNode->pNextNode;
                }
            }
        }
        free(auxiNode);
        this->size --;
        returnAux=0;
    }
    return returnAux;
}


 //Elimina todos los elementos de la lista
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int tam;
    if(this!=NULL)
    {
        tam=ll_len(this);
        while(tam != -1)
        {
            ll_remove(this,tam);
            tam--;
        }
        returnAux=0;
    }
    return returnAux;
}



 //Elimina todos los elementos de la lista y la lista
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        if(!ll_clear(this))
        {
            free(this);
            returnAux = 0;
        }
    }
    return returnAux;
}


 //Busca el indice de la primer ocurrencia del elemento pasado como parametro
int ll_indexOf(LinkedList* this, void* pElement)//muestra el primer elemento.
{
    int returnAux = -1;

    if(this!= NULL)
    {
        for (int i = 0; i < ll_len(this); i++)
        {
            if (ll_get(this, i) == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }

    return returnAux;
}

 //Indica si la lista esta o no vacia
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux=ll_len(this)? 0:1;
        //Esto resume el if else
        /*  if(ll_len(this)!=0)
          {
              returnAux=0;
          }
          else
          {
              returnAux=1;
          }*/
    }

    return returnAux;
}

 //Inserta un nuevo elemento en la lista en la posicion indicada
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && index >=0 && index <= ll_len(this))
    {
        if(!addNode(this,index,pElement))
        {
            returnAux=0;
        }
    }
    return returnAux;
}


//Elimina el elemento de la posicion indicada y retorna su puntero
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    if(this != NULL && index >=0 && index < ll_len(this))
    {

        returnAux=(void*)ll_get(this,index);
        if(returnAux!=NULL)
        {
            ll_remove (this, index);
        }
    }

    return returnAux;

}



//Determina si la lista contiene o no el elemento pasado como parametro
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        if(ll_indexOf(this,pElement)!= -1)
        {
            returnAux=1;
        }
        else
        {
            returnAux=0;
        }
    }
    return returnAux;
}


//Determina si todos los elementos de la lista (this2)  estan contenidos en la lista (this)
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    if(this != NULL && this2 != NULL)
    {
        returnAux=1;
        for(i=0; i<ll_len(this2); i++)
        {
            if(!ll_contains(this, ll_get(this2,i)))
                returnAux=0;
            break;
        }
    }
    return returnAux;
}


//Crea y retorna una nueva lista con los elementos indicados
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from >=0 && from < to &&  to <= ll_len(this))
    {
        cloneArray=ll_newLinkedList();
        if(cloneArray!= NULL)
        {
            while(from!=to)
            {
                ll_add(cloneArray, ll_get(this,from));
                from++;
            }
        }
    }
    return cloneArray;
}


//Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!= NULL)
    {
        cloneArray=ll_subList(this,0,ll_len(this));

    }
    return cloneArray;
}


//Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int i,j;
    void* pElement1;
    void* pElement2;
    if(this!= NULL && pFunc != NULL && (order ==0 || order == 1))
    {
        for(i=0; i<ll_len(this); i++)
        {
            pElement1=ll_get(this,i);
            for(j=i+1; j<ll_len(this); j++)
            {
                pElement2=ll_get(this,j);
                if(order == 1)
                {
                    if(pFunc(pElement1,pElement2)>0)
                    {
                        ll_set(this,i,pElement2);
                        ll_set(this,j,pElement1);
                        pElement1=pElement2;
                    }
                }
                else
                {
                    if(pFunc(pElement1,pElement2)<=0)
                    {
                        ll_set(this,i,pElement2);
                        ll_set(this,j,pElement1);
                        pElement1=pElement2;
                    }
                }
            }
        }
        returnAux=0;
    }

    return returnAux;

}


LinkedList* ll_map(LinkedList* this,void (*fn)(void* element))
{
    void* pElemen;
   // void* aux;
    int i;
    if(this != NULL && fn != NULL )
    {
        for(i=0;i<ll_len(this);i++)
        {
             pElemen=ll_get(this,i);
             fn(pElemen);
             ll_set(this,i,pElemen);
        }
    }
    return this;
}
/* Ejemplo de funcion fn
void calcularPrecioFinal(Producto* p)
{
    if(p != NULL)
    {
        p->precioFinal = p->precioUnitario*p->cantidad;
    }
return;
}*/


LinkedList* ll_filter(LinkedList* this, int(*fn)(void*))
{
    LinkedList* this2=NULL;
    void* pElemento;
    int i;
    if(this != NULL && fn != NULL)
    {
        this2=ll_newLinkedList();
        if(this2!=NULL)
        {
            for(i=0;i<ll_len(this);i++)
            {
                pElemento=ll_get(this,i);
                if(fn(pElemento))
                {
                    ll_add(this2,pElemento);
                }
            }
        }

    }
    return this2;
}
/*EJEMPLO DE COMO SE USARIA O COMO SERIA
int filtrarMujeres(eEmpleado* emp)
{
    int retorno = 0;
    if(emp != NULL){

     if(eEmpleado->sexo == 'f'){
        retorno = 1;
     }

    }
    return retorno;
}
*/
