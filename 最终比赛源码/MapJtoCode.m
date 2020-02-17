%输出MapJ至txt
%1025补充功能，输出左边界，即每一行中=2的位置和右边界，即每一行中等于77的位置。

fid=fopen('MapJcode.txt','w');

LeftBorder=zeros(60,1);
RightBorder=zeros(60,1);

fprintf(fid,'int MapJ[60*80]={');
for i=1:60
    fprintf(fid,'\n');
    for j=1:80
    
        fprintf(fid,'%d,',MapJ(i,j));
        
        if MapJ(i,j)==2
            LeftBorder(i)=j-1;
        elseif MapJ(i,j)==77
            RightBorder(i)=j-1;    
        end
        
    end
end


fprintf(fid,'};\n');

fprintf(fid,'uint8 LeftBorder[60]={');

for i=1:60
    if LeftBorder(i)==0
        LeftBorder(i)=LeftBorder(i-1);
    end
    fprintf(fid,'%d,',LeftBorder(i));
    
end
fprintf(fid,'};\n');

fprintf(fid,'uint8 RightBorder[60]={');

for i=1:60
    if RightBorder(i)==0
        RightBorder(i)=RightBorder(i-1);
    end
    fprintf(fid,'%d,',RightBorder(i));
    
end
fprintf(fid,'};\n');

fclose(fid);