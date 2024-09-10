#include <iostream>
#include <opencv2/opencv.hpp>
#include "../include/game.hpp"
using namespace std;
using namespace cv;

// Fungsi untuk memeriksa tabrakan antara dua lingkaran
bool collision(Point &bola, Point2f &lingkaran, int radiusBola, int radiusLingkaran) {
   // Hitung jarak Euclidean antara pusat dua lingkaran
   double distance = sqrt(pow(bola.x - lingkaran.x, 2) + pow(bola.y - lingkaran.y, 2));

   // Periksa jika jarak kurang dari atau sama dengan jumlah radius kedua lingkaran
   return distance <= (radiusBola + radiusLingkaran);
}

int main(){
   VideoCapture kamera;
   peluru peluru(Point(240,0),10,10);
   Mat frame;
   int score = 0;
   kamera.open(0);
   if(kamera.isOpened()){
      while(1){
         kamera >> frame;
         if(frame.empty()){
            cerr << "frame kosong" << endl;
            return 1;
         }

         Mat frame_clone = frame.clone();
         cvtColor(frame_clone,frame_clone,COLOR_BGR2HSV);

         Mat limcolor;
         inRange(frame_clone,Scalar(0, 159, 116), Scalar(179, 255, 168),limcolor);

         vector<vector<Point>> kontur;
         findContours(limcolor, kontur, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

         //score
         string teks = "SCORE: " +  std::to_string(score);
         putText(frame,teks,cv::Point(10,100),cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,255,255),1);

         circle(frame,peluru.position,peluru.radius,Scalar(255,255,255),-1);

         // Variabel untuk menyimpan pusat dan radius lingkaran yang terdeteksi
         Point2f pusat_lingkaran;
         float radius_lingkaran = 10;
         bool lingkaran_ditemukan = false;

         for (size_t i = 0; i < kontur.size(); i++) {
            // Mendeteksi lingkaran dengan minimum enclosing circle
            minEnclosingCircle(kontur[i], pusat_lingkaran, radius_lingkaran);

            // Gambarkan lingkaran pada frame
            circle(frame, pusat_lingkaran, (int)radius_lingkaran, Scalar(0, 255, 0), 2);

            lingkaran_ditemukan = true; // Tandai bahwa lingkaran telah ditemukan
         }

         peluru.move_peluru();
         peluru.koresi_layar(480,640);

         if (lingkaran_ditemukan) {
            // Panggil fungsi collision
            if (collision(peluru.position, pusat_lingkaran, peluru.radius, (int)radius_lingkaran)) {
               peluru.position = Point(240,0);
               score += 1;
            }
         }

         namedWindow("kamera",WINDOW_AUTOSIZE);
         imshow("kamera",frame);
         // //tau saja
         // int kolom = frame.cols;
         // int row = frame.rows;
         // cout << "kolom:" << kolom << " row:" << row << endl;
         if(waitKey(5) == 32){
            break;
         }
      }
   }else{
      cerr << "salah membuka kamera" << endl;
      return 1;
   }
   return 0;
}