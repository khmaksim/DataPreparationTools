# -*- coding: utf-8 -*-

import arcpy

rows = []

def addLineData(data):
    rows = data.split(';')
    print(rows)

def createShp(name, path_to_result):
    print('Start create shp-file')
    # Set variables
    arcpy.env.workspace = path_to_result.replace('\\', '/')
    arcpy.env.overwriteOutput = True
    work_path = path_to_result.replace('\\', '/')
    result_shp = name + '.shp'
    workspace = work_path

    sr = arcpy.SpatialReference(26915)

    if name == 'airways':
        arcpy.CreateFeatureclass_management(out_path=work_path, out_name=result_shp, geometry_type='POLYLINE', spatial_reference = sr)
        arcpy.AddField_management(result_shp, 'NAME','TEXT')
        arcpy.AddField_management(result_shp, 'RTE_POINTS','TEXT')
        arcpy.AddField_management(result_shp, 'ik1','TEXT')
        arcpy.AddField_management(result_shp, 'ik2','TEXT')
        arcpy.AddField_management(result_shp, 'HMIN','TEXT')
        arcpy.AddField_management(result_shp, 'HMAX','TEXT')
        arcpy.AddField_management(result_shp, 'LENGTH_KM','SHORT')
        arcpy.AddField_management(result_shp, 'SEM_311','FLOAT')
        arcpy.AddField_management(result_shp, 'SEM_312','FLOAT')
        arcpy.AddField_management(result_shp, 'COUNTRY','TEXT')
        arcpy.AddField_management(result_shp, 'LINE_TYPE','TEXT')
        arcpy.AddField_management(result_shp, 'RTE_TYPE','TEXT')
        arcpy.AddField_management(result_shp, 'ZZZ','LONG')

        with arcpy.da.InsertCursor(result_shp, ['NAME', 'RTE_POINTS', 'ik1', 'ik2', 'HMIN', 'HMAX',
        'LENGTH_KM', 'COUNTRY', 'LINE_TYPE', 'RTE_TYPE']) as cursor:
            for row in rows:
                name = row[0]
                rte_point = row[1] + '-' + row[2]
                ik1 = row[3]
                ik2 = row[4]
                h_min = row[5] + str(row[6])
                h_max = row[7] + str(row[8])
                length = row[9]
                country = row[10]
                line_type = 'INTER'
                rte_type = row[11]
                cursor.insertRow([name, rte_point, ik1, ik2, h_min, h_max, length, country, line_type, rte_type])
        del cursor
    elif name == 'points':
        arcpy.CreateFeatureclass_management(out_path=work_path, out_name=result_shp, geometry_type='POINT', spatial_reference = sr)
        arcpy.AddField_management(result_shp, 'TYP','TEXT')
        arcpy.AddField_management(result_shp, 'DESIGNATOR','TEXT')
        arcpy.AddField_management(result_shp, 'LATITUDE','FLOAT')
        arcpy.AddField_management(result_shp, 'LONGITUDE','FLOAT')
        arcpy.AddField_management(result_shp, 'ID','LONG')
        arcpy.AddField_management(result_shp, 'COUNTRY','TEXT')
        arcpy.AddField_management(result_shp, 'Notes','TEXT')
        arcpy.AddField_management(result_shp, 'ZZZ','LONG')

        with arcpy.da.InsertCursor(result_shp, ['TYP', 'DESIGNATOR', 'LATITUDE', 'LONGITUDE', 'ID',
        'COUNTRY', 'Notes', 'ZZZ']) as cursor:
            for row in rows:
                type = row[0]
                designator = row[1]
                lat = row[2]
                lon = row[3]
                id = row[4]
                country = row[5]
                notes = ''
                zzz = 0
                cursor.insertRow([type, designator, lat, lon, id, country, notes, zzz])
        del cursor
    print('End create shp-file')
