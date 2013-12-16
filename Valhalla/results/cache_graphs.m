function [totalCPI, l1InstHitRate, l1dataHitRate, l2dataHitRate] = cache_graphs(cacheName, fileList)
[numberReads, numberWrites, numberInst, numberCycleReads, numberCycleWrites, numberCycleInst] = deal(0,0,0,0,0,0);
[L1iHit, L1dHit, L2dHit, L1iReq, L1dReq, L2dReq] = deal(0,0,0,0,0,0);

cacheNameSpace = strrep(cacheName, '_', ' ');

for i = 1:(length(fileList))
    A = importdata(fileList{i});
    numberReads = numberReads + str2double(A.textdata(14,3));
    numberWrites = numberWrites + str2double(A.textdata(15,3));
    numberInst = numberInst + str2double(A.textdata(16,3));
    numberCycleReads = numberCycleReads + str2double(A.textdata(19,3));
    numberCycleWrites = numberCycleWrites + str2double(A.textdata(20,3));
    numberCycleInst = numberCycleInst + str2double(A.textdata(21,3));
    L1iHit = L1iHit + str2double(A.textdata(26,4));
    L1iReq = L1iReq + str2double(A.textdata(27,4));
    L1dHit = L1dHit + str2double(A.textdata(31,4));
    L1dReq = L1dReq + str2double(A.textdata(32,4));
    L2dHit = L2dHit + str2double(A.textdata(36,4));
    L2dReq = L2dReq + str2double(A.textdata(37,4));
end

cpi(1) = (numberCycleReads)/(numberReads);
cpi(2) = (numberCycleWrites)/(numberWrites);
cpi(3) = (numberCycleInst)/(numberInst);
cpi(4) = (numberCycleReads+numberCycleWrites+numberCycleInst)/(numberReads+numberWrites+numberInst);
totalCPI = cpi(4);
cpiGraph = figure('units','normalized','outerposition',[0 0 1 1]);
hold on;
h = bar(1,cpi(1));
set(h, 'FaceColor', 'r');
h = bar(2,cpi(2));
set(h, 'FaceColor', 'b');
h = bar(3,cpi(3));
set(h, 'FaceColor', 'g');
h = bar(4,cpi(4));
set(h, 'FaceColor', 'k');
title(strcat(cacheNameSpace,' CPI'));
set(gca,'XTick',[]);
ylabel('CPI');
legend('Read CPI', 'Write CPI', 'Instruction CPI', 'Total CPI', 'Location', 'NorthEastOutside');
hold off;

saveas(cpiGraph, strcat(cacheName,'_CPI_Graph'), 'png');

hitRate(1) = (L1iHit/L1iReq)*100;
l1InstHitRate = hitRate(1);
hitRate(2) = (L1dHit/L1dReq)*100;
l1dataHitRate = hitRate(2);
hitRate(3) = (L2dHit/L2dReq)*100;
l2dataHitRate = hitRate(3);

hitRateGraph = figure('units','normalized','outerposition',[0 0 1 1]);
hold on;
h = bar(1,hitRate(1));
set(h, 'FaceColor', 'r');
h = bar(2,hitRate(2));
set(h, 'FaceColor', 'b');
h = bar(3,hitRate(3));
set(h, 'FaceColor', 'g');
title(strcat(cacheNameSpace,' Hit Rates'));
set(gca,'XTick',[]);
ylabel('Hit Rate');
ylim([min(hitRate)-10,100]);
legend('Level 1 Instruction Cache Hit Rate', 'Level 1 Data Cache Hit Rate', 'Level 2 Cache Hit Rate', 'Location', 'NorthEastOutside');
hold off;

saveas(hitRateGraph, strcat(cacheName,'_Hit_Rate_Graph'), 'png');