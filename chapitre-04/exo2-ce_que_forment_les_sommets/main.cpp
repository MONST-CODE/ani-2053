#include <iostream>
#include <string>

int main()
{
    long long Nombre_total_de_Points = 0;
    long  long nombre_de_triangles = 0;
    long long s ;
    long long nombredelignes = 0;
    enum Types {POINTS,LINES,LINE_STRIP,TRIANGLES,TRIANGLE_STRIP,TRIANGLE_FAN=TRIANGLE_STRIP,QUADS,quads=QUADS};

    std::string typeSaisi;
    long long rest = 0; 
    long long comp =0;
    long long refuser=0;

    // 1. On lit des chaînes de caractères avec std::cin
    std::cin >> typeSaisi >> s;

    // 2. On convertit la chaîne en valeur enum
    Types monType;
    if (typeSaisi == "POINTS") monType = POINTS;
    else if (typeSaisi == "LINES") monType = LINES;
    else if (typeSaisi == "LINE_STRIP") monType = LINE_STRIP;
    else if (typeSaisi == "TRIANGLES") monType = TRIANGLES;
    else if (typeSaisi == "TRIANGLE_STRIP") monType = TRIANGLE_STRIP;
    else if (typeSaisi == "TRIANGLE_FAN") monType = TRIANGLE_FAN;
    else if (typeSaisi == "QUADS") monType = QUADS;
    else if (typeSaisi == "quads") monType = quads;
    else {
        std::cerr << "Type inconnu : " << typeSaisi << "\n";
        return 1;
    }
    //if
    if (monType == POINTS )
    
    {
        
        comp=s;rest=s;
        std::cout << "POINTS" << " " << s <<" " << comp << " POINTS " << rest << "\n";
      if (monType == LINES) {
        if((s%2) == 0){
            comp=s/2;
        }else{
            comp=(s-1)/2;
        }
        rest = s%2;
        nombredelignes =comp;
        std::cout << "LINES" << " " << s <<" " << comp <<" LINES "<< rest << "\n";
      }
      if (monType == LINE_STRIP)
      {
        if(s<2 || s==0){
            rest = 1;
        std::cout << "LINES_STRIP" << " " << s <<" " << comp <<" LINES_STRIP " << rest << "\n";
        }else{
            comp = s-1;
            std::cout << "LINES_STRIP" << " " << s <<" " << comp << " LINES_STRIP " << rest << "\n";
        }
      }
      if(monType == quads) {
        nombredelignes +=comp;
        
        std::cout<<"QUADS "<<refuser<<std::endl;
       }
       if (monType == TRIANGLES)
       {
        if(s%3 == 0){
            comp = s/3;
        }
        if(s%3 == 1){
            comp = (s-1)/3;
            
        }
        if(s%3 == 2){
            comp = (s-2)/3;
        }
        rest = s%3;
        nombre_de_triangles +=comp;
        std::cout << "TRIANGLES" << " " << s  <<" " << comp << " TRIANGLES " << rest << "\n";
       
       }
       if(monType == TRIANGLE_FAN || monType == TRIANGLE_STRIP){
        if(s>=3)
        {
            comp = s-2;
            rest = 0;
        }else{
            comp = 0;
            rest = s;
        }
        nombre_de_triangles +=comp;
        std::cout << "TRIANGLES_FAN" << " " << s  <<" "  << comp << " TRIANGLES_FAN " << rest << "\n";
        }
       }
    if(monType == QUADS || monType == quads)
    {
        ++refuser;
    };
    Nombre_total_de_Points = s;

    std::cout << "POINTS " << Nombre_total_de_Points << '\n';
    std::cout << "SEGMENTS " << nombredelignes << '\n';
    std::cout << "TRIANGLES " << nombre_de_triangles << '\n';
    std::cout << "REFUSER " << refuser << '\n';

    std::cin>>s;
}

