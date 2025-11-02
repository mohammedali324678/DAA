#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 10
#define INF 999999
#define R 6371.0
#define PI 3.141592653589793
double rad(double x) { return x * PI / 180; }
double distance(double lat1, double lon1, double lat2, double lon2){
    double dlat = rad(lat2 - lat1);
    double dlon = rad(lon2 - lon1);
    lat1 = rad(lat1); lat2 = rad(lat2);
    double a = sin(dlat/2)*sin(dlat/2) + cos(lat1)*cos(lat2)*sin(dlon/2)*sin(dlon/2);
    return R * 2 * atan2(sqrt(a), sqrt(1-a));
}
void prims(int n, char city[MAX][50], double lat[MAX], double lon[MAX]){
    double cost[MAX][MAX], total=0;
    int sel[MAX] = {0}, edges=0;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cost[i][j] = (i==j? INF : distance(lat[i],lon[i],lat[j],lon[j]));

    sel[0]=1;
    printf("\nEdges in MST:\n");
    while(edges < n-1){
        double min = INF;
        int x=-1, y=-1;
        for(int i=0;i<n;i++) if(sel[i])
            for(int j=0;j<n;j++) if(!sel[j] && cost[i][j] < min){
                min = cost[i][j]; x=i; y=j;
            }
        printf("%s - %s : %.2lf km\n", city[x], city[y], cost[x][y]);
        total += cost[x][y]; sel[y]=1; edges++;
    }
    printf("Total minimum cost = %.2lf km\n", total);
}

int main(){
    int n;
    char city[MAX][50];
    double lat[MAX], lon[MAX];

    // Part A: Same state cities
    printf("Enter number of cities in same state (4-6): ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter city name, latitude, longitude: ");
        scanf("%s %lf %lf", city[i], &lat[i], &lon[i]);
    }
    printf("\n--- MST for same-state cities ---\n");
    prims(n, city, lat, lon);

    // Part B: Different state cities
    printf("\nEnter number of cities in different states (4-6): ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("Enter city name, latitude, longitude: ");
        scanf("%s %lf %lf", city[i], &lat[i], &lon[i]);
    }
    printf("\n--- MST for different-state cities ---\n");
    prims(n, city, lat, lon);

    return 0;
}
