% call cache_graphs with each different configuration with 
% all cache simulation results for that configuration.

close all;
set(0,'DefaultFigureVisible','off');

fileList = dir('*.2-4-way');
fileNames = extractfield(fileList, 'name');
[totalCPI(1), hitRate(1,1), hitRate(1,2), hitRate(1,3)] = cache_graphs('L1_2_way_L2_4_way', fileNames);

fileList = dir('*.All-2way');
fileNames = extractfield(fileList, 'name');
[totalCPI(2), hitRate(2,1), hitRate(2,2), hitRate(2,3)] = cache_graphs('All_2_way', fileNames);

fileList = dir('*.All-FA');
fileNames = extractfield(fileList, 'name');
[totalCPI(3), hitRate(3,1), hitRate(3,2), hitRate(3,3)] = cache_graphs('Fully_Associative', fileNames);

fileList = dir('*.default');
fileNames = extractfield(fileList, 'name');
[totalCPI(4), hitRate(4,1), hitRate(4,2), hitRate(4,3)] = cache_graphs('Direct_Mapped', fileNames);

fileList = dir('*.L1-2way');
fileNames = extractfield(fileList, 'name');
[totalCPI(5), hitRate(5,1), hitRate(5,2), hitRate(5,3)] = cache_graphs('L1_2_way', fileNames);

fileList = dir('*.L2-2way');
fileNames = extractfield(fileList, 'name');
[totalCPI(6), hitRate(6,1), hitRate(6,2), hitRate(6,3)] = cache_graphs('L2_2_way', fileNames);

fileList = dir('*.L2-Big');
fileNames = extractfield(fileList, 'name');
[totalCPI(7), hitRate(7,1), hitRate(7,2), hitRate(7,3)] = cache_graphs('L2_Big', fileNames);

totalCPIGraph = figure('units','normalized','outerposition',[0 0 1 1]);
faceColors = ['r','g','b','k','c','m','y'];
hold on;

for i = 1:length(totalCPI)
    h = bar(i, totalCPI(i));
    set(h, 'FaceColor', faceColors(i));
end
title('Total CPI for All Memory Configurations');
set(gca,'XTick',[]);
ylabel('CPI');
legend('L1 2 way L2 4 way', 'All 2 way', 'Fully Associative', 'Direct Mapped', 'L1 2 way', 'L2 2 way', 'L2 Big', 'Location', 'NorthEastOutside');
hold off;

saveas(totalCPIGraph, 'CPI_Graph_All_Configurations', 'png');

set(0,'DefaultFigureVisible','on');
close all;

totalHitRateGraph = figure('units','normalized','outerposition',[0 0 1 1]);
hold on;

bar(hitRate,'grouped');

title('Hit Rate for All Memory Configurations');
set(gca,'XTick',1:7)
set(gca,'XTickLabel',{'L1 2 way L2 4 way', 'All 2 way', 'Fully Associative', 'Direct Mapped', 'L1 2 way', 'L2 2 way', 'L2 Big'})
ylabel('Hit Rate');
legend('L1 InstructionCache Hit Rate', 'L1 Data Cache Hit Rate', 'L2 Cache Hit Rate', 'Location', 'NorthEastOutside');
ylim([60 100]);
hold off;

saveas(totalHitRateGraph, 'Hit_Rate_Graph_All_Configurations', 'png');