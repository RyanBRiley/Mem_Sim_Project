% call cache_graphs with each different configuration with 
% all cache simulation results for that configuration.

close all;
set(0,'DefaultFigureVisible','off')

fileList = dir('*.2-4-way');
fileNames = extractfield(fileList, 'name')
cache_graphs('L1_2_way_L2_4_way', fileNames)

fileList = dir('*.All-2way');
fileNames = extractfield(fileList, 'name')
cache_graphs('All_2_way', fileNames);

fileList = dir('*.All-FA');
fileNames = extractfield(fileList, 'name')
cache_graphs('Fully_Associative', fileNames);

fileList = dir('*.default');
fileNames = extractfield(fileList, 'name')
cache_graphs('Direct_Mapped', fileNames);

fileList = dir('*.L1-2way');
fileNames = extractfield(fileList, 'name')
cache_graphs('L1_2_way', fileNames);

fileList = dir('*.L2-2way');
fileNames = extractfield(fileList, 'name')
cache_graphs('L2_2_way', fileNames);

fileList = dir('*.L2-Big');
fileNames = extractfield(fileList, 'name')
cache_graphs('L2_Big', fileNames);