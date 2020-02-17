%MapJ Test
%测试MapJ的矫正效果

load('MapJ.mat');

img=imread('Example1.bmp');

imgCT=uint8(zeros(60,80));

for i=1:60
    
   for j=1:80 
    
       jCT=MapJ(i,j)+1;
       
       if jCT>80
       
           imgCT(i,j)=100;
           
       else
           
           imgCT(i,j)=img(i,jCT,1);
           
       end
           
   end
    
end

imshow(imgCT);