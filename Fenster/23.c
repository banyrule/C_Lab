/*Задание 23. Обход в ширину*/ 
// для проверки:
// 0 2
// 0 4
// 0 6
// 1 9
// 2 0
// 2 3
// 3 2
// 3 4
// 4 0
// 4 3
// 6 0
// 6 7
// 6 8
// 7 6
// 8 6
// 9 1
// должно вывести 0 2 3 4 6 7 8, при начальной вершине 0
#include <stdio.h>
#define N 100

int n, from, to;
int a[N][N]; 
int used[N], d[N], p[N];
/*а - матрица смежности, used - пройденые вершины, 
d - расстояние от начальной вершины, p - предки вершин*/ 
int queue[N];
int r = 0, w = 0;

void enqueue(int a){
	queue[w++] = a;
}

int dequeue(void){
	return (queue[r++]);
}

int empty(void){
	return (r == w);
}

void bfs(int v){
	if(used[v]) //если вершина уже пройдена, то не производим из нее вызов процедуры
		return;
	enqueue(v);	//кладем начальную вершину v в очередь
	used[v] = 1; //помечаем вершину v как посещенную
	d[v] = 0; //расстояние от вершины v до самой себя равно 0
	while(!empty()){
		v = dequeue(); //продолжаем обход из вершины v, находящейся в «голове» очереди
		for (int w = 0; w < N; ++w) //обрабатываем ребро (v, w)
			if(!used[w] && a[v][w]){
				enqueue(w); //если вершина w является не посещенной, то добавляем ее в очередь
				used[w] = 1; //помечаем вершину w как посещенную	
				p[w] = v; //помечаем предком вершины w вершину v
				d[w] = d[v] + 1; //обновляем расстояние от начальной вершины обхода до вершины w
			}
	}

}

int main(void){

	//инициализация нулями
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			a[i][j] = 0;
		used[i] = 0;
		d[i] = 9999;
		p[i] = -1;
	}

	// чтение ребер
	while(scanf("%d %d", &from, &to) == 2){
		a[from][to] = 1;
		a[to][from] = 1;
	}

	//обход
	bfs(0);

	//вывод вершин, достижимых из стартовой
	for (int i = 0; i < N; ++i)
		if(used[i])
			printf("%d \n", i);

	return 0;
}