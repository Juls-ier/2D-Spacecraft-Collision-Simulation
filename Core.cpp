#include "Core.h"
#include <cmath>
#include <sstream>
#include <fstream>

Point::Point(double x, double y) : x(x), y(y) {}
Object::Object() : center_position(0.0f, 0.0f), velocity(0.0f, 0.0f) {}
Missile::Missile(double t, Point pos, Point vel) : time(t), base_position(pos), velocity(vel){}
Collision::Collision(double t, Point pos) : time (t) , position(pos){}


void Mesh::create_object(std::string path, std::string path2) {

	Object * created = new Object();


	created->load_points(path);

   // created->jarvis_convex()

    created->quickhull_convex();
    created->load_position(path2);



	objects.push_back(created);
}



 void vector_change(Point &p, Point vector){

     p.x += vector.x;
     p.y += vector.y;

}



 void Object::update_position() {


     Point step(velocity.x * 0.1, velocity.y * 0.1);

     for (int i = 0; i < points.size(); i++) {
         vector_change(points[i], step);
     }
     for (int i = 0; i < convex.size(); i++) {
         vector_change(convex[i], step);
     }

 }

 void Object::load_position(std::string path) {

     std::fstream file(path);

     if (!file.is_open())
     {
         std::cout << "nie wczyt pozycji\n";
         return;
     }

     double x, y;
     file >> x >> y;
     center_position = Point(x,y);
     
     file >> x >> y;
     velocity = Point(x, y);

     double x_sum = 0;
     double y_sum = 0;

     for (int i = 0; i < points.size(); i++) {
         x_sum += points[i].x;
         y_sum += points[i].y;

     }

     Point center = Point(x_sum / points.size(), y_sum / points.size());
     Point vector = Point(center_position.x - center.x, center_position.y - center.y);

     for (int i = 0; i < points.size(); i++) {
         vector_change(points[i], vector);
     }
     for (int i = 0; i < convex.size(); i++) {
         vector_change(convex[i], vector);
     }

 }


void Object::load_points(std::string path) {

    std::fstream file(path);

    if (!file.is_open())
    {
        std::cout << "nie wczyt pkt\n";
        return;
    }


    double x;
    double y;

    while (file >> x >> y) {

        points.push_back(Point(x, y));

    }
    return;
}



int side_check(Point p1, Point p2, Point p3) {

    double val = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (val > tolerance) {
        return -1; // lewo
    }
    if (val < -tolerance) {
        return 1;  // prawo
    }

    return 0; // na lini
}




void Object::jarvis_convex() {

    Point p1 = points[0]; //min
    Point q1 = points[0]; //max

    int y2 = 1000;

    for (int i = 0; i < points.size(); i++) {

        if (points[i].y < p1.y) {
            p1 = points[i];
        }
        else if (points[i].y == p1.y && points[i].x < p1.x) {
            p1 = points[i];
        }

        if (points[i].y > q1.y) {
            q1 = points[i];
        }
        else if (points[i].y == q1.y && points[i].x > q1.x) {
            q1 = points[i];
        }
    }

    Point cur = p1;


    do {
        convex.push_back(cur);
        Point possibl = points[0];

        for (int i = 1; i < points.size(); i++) {

            if (side_check(cur, possibl, points[i]) > 0) {
                possibl = points[i];
            }

        }

        cur = possibl;



    } while (abs(cur.x - p1.x) > tolerance || abs(cur.y - p1.y) > tolerance);



}



double distance(Point p1, Point p2, Point p3) { ///nie pelna! tylko do porownania
    return std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}

double length(Point a, Point b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

void Object::convex_fix() {

    double max_length = 50;

    for (int i = 0; i < convex.size(); i++) {

        if (i == convex.size() - 1) {

            if (length(convex[i], convex[0]) >= max_length){
                Point act = convex[i];
                convex[i] = Point((convex[i].x + convex[0].x) / 2, (convex[i].y + convex[0].y) / 2);
                convex.push_back(act);
            }

        }
        else {
            if (length(convex[i], convex[0]) >= max_length) {
                

                convex.insert(convex.begin()+i +1, Point((convex[i].x + convex[i + 1].x) / 2, (convex[i ].y + convex[i+1].y) / 2));
                  
                
            }

        }


    }


}




void Object::quickhull_recur(Point A, Point B, std::vector <Point> side) {

    if (side.empty()) {
        return;
    }

    if (side.size() == 1) {
        convex.push_back(side[0]);
        return;
    }

    Point max = side[0];
    for (int i = 0; i < side.size(); i++) {

        if (distance(A, B, side[i]) > distance(A, B, max) + tolerance) {

            max = side[i];
        }

    }


    std::vector<Point> left_ac;
    std::vector<Point> left_cb;

    for (int i = 0; i < side.size(); i++) {
    
        if (side_check(A, max, side[i]) < 0) {
            left_ac.push_back(side[i]);
        }

        if (side_check(max, B, side[i] ) < 0) {
            left_cb.push_back(side[i]);
        }
    
    }

    quickhull_recur(A, max, left_ac);
    convex.push_back(max);
    quickhull_recur(max,B, left_cb);

}


void Object::quickhull_convex() {
    


    Point p1 = points[0]; //min
    Point q1 = points[0]; //max

    int y2 = 1000;

    for (int i = 0; i < points.size(); i++) {

        if (points[i].x < p1.x) {
            p1 = points[i];
        }
        if (points[i].x > q1.x) {
            q1 = points[i];
        }
    }

    std::vector <Point> left;
    std::vector <Point> right;

    for (int i = 0; i < points.size(); i++) {
        int check = side_check(p1, q1, points[i]);
        if (check>0) {

            right.push_back(points[i]);

        }
        else if (check < 0) {
            left.push_back(points[i]);
        }

    }
    convex.push_back(p1);
    quickhull_recur(p1, q1, left);

    convex.push_back(q1);
    quickhull_recur(q1, p1, right);

}

void Mesh::load_missiles(std::string path) {

    std::fstream file(path);

    if (!file.is_open())
    {
        std::cout << "nie wczyt pociskow\n";
        return;
    }


    double t, x, y, xv, yv;

    while (file >>t>>x >> y>>xv>>yv) {

        missiles.push_back(Missile(t, Point(x, y), Point(xv, yv)));

    }


}

void Missile::update_position(double t) {


    Point step(velocity.x * t, velocity.y * t);

        vector_change(base_position, step);

}


Point crossing(Point A, Point B, Point C, Point D) {

    double r_x = B.x - A.x;
    double r_y = B.y - A.y;
    double s_x = D.x - C.x;
    double s_y = D.y - C.y;

  
    double r_cross_s = r_x * s_y - r_y * s_x;

   
    if (std::abs(r_cross_s) < tolerance) {
        return Point(-10000, -10000);
    }

    
    double t = ((C.x - A.x) * s_y - (C.y - A.y) * s_x) / r_cross_s;

    double x = A.x + t * r_x;
    double y = A.y + t * r_y;

    return Point(x, y);

}

void Mesh::check_collision() {

    Object * ship = objects[0];
    std::vector<Point> dense;

    double den = 5000;

    for (int j = 0; j < ship->convex.size(); j++) {
        Point p1 = ship->convex[j];
       
        Point p2 = Point(0, 0);
        
        if (j == ship->convex.size() - 1) {
            p2 = ship->convex[0];
        }
        else {
            p2 = ship->convex[j + 1]; 
        }
        for (double k = 0; k < den; k++) {
            double ratio = k / den;
            double nx = p1.x + (p2.x - p1.x) * ratio;
            double ny = p1.y + (p2.y - p1.y) * ratio;
            dense.push_back(Point(nx, ny));
        }
    }
        





    for (int i = 0; i < missiles.size(); i++) {

        Missile cur = missiles[i];
        Point end_missile(cur.base_position.x + cur.velocity.x * (2 - cur.time), cur.base_position.y + cur.velocity.y * (2 - cur.time));

        for (int j = 0; j < dense.size(); j++) {

            Point end_ship(dense[j].x + (ship->velocity.x *2), dense[j].y + (ship->velocity.y *2));
            Point collision = crossing(dense[j], end_ship, cur.base_position, end_missile);
            if (collision.x != -10000 && collision.y != -10000) {


                double time = (collision.x - dense[j].x) / ship->velocity.x;
                double time_missile = ((collision.x - cur.base_position.x) / cur.velocity.x) + cur.time;
                if (time > 0 && time <= 2 ) {
                    if (abs(time - time_missile) < 0.0001) {
                        std::cout << "kolizja w punkcie : " << collision.x << " " << collision.y << " po " << time << "s" << std::endl;
                       

                        collisions.push_back(Collision(time, collision));
                       

                    }
                }
            }
        }


    }



}

void Mesh::update_collision(Collision &col ,Point vector, double time) {

    Point step(vector.x * time, vector.y * time);
    col.position.x += vector.x * time;
    col.position.y += vector.y * time;

    
}