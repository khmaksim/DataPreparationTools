# -*- coding: utf-8 -*-

import arcpy

rows = []

def addLineData(data):
    row = data.split(';')
    rows.append(row)
    print(row)

def createShp(name, path_to_result):
    print('Start create shp-file')
    # Set variables
    arcpy.env.workspace = path_to_result.replace('\\', '/')
    arcpy.env.overwriteOutput = True
    arcpy.ClearWorkspaceCache_management()
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
                name_airway = row[0]
                rte_point = row[1] + '-' + row[2]
                ik1 = row[3]
                ik2 = row[4]
                h_min = row[5] + str(row[6])
                h_max = row[7] + str(row[8])
                length = row[9]
                country = row[10]
                line_type = 'INTER'
                rte_type = row[11]
                cursor.insertRow([name_airway, rte_point, ik1, ik2, h_min, h_max, length, country, line_type, rte_type])
        del cursor
    elif name == 'points':
        arcpy.CreateFeatureclass_management(out_path=work_path, out_name=result_shp, geometry_type='POINT', spatial_reference = sr)
        arcpy.AddField_management(result_shp, 'TYP','TEXT')
        arcpy.AddField_management(result_shp, 'DESIGNATOR','TEXT')
        arcpy.AddField_management(result_shp, 'LATITUDE','TEXT')
        arcpy.AddField_management(result_shp, 'LONGITUDE','TEXT')
        arcpy.AddField_management(result_shp, 'ID_','LONG')
        arcpy.AddField_management(result_shp, 'COUNTRY','TEXT')
        arcpy.AddField_management(result_shp, 'Notes','TEXT')
        arcpy.AddField_management(result_shp, 'ZZZ','LONG')

        with arcpy.da.InsertCursor(result_shp, ['TYP', 'DESIGNATOR', 'LATITUDE', 'LONGITUDE', 'ID_', 'COUNTRY']) as cursor:
            for row in rows:
                type_point = row[0]
                designator = row[1]
                lat = row[2]
                lon = row[3]
                id_point = long(row[4])
                country = row[5]
                cursor.insertRow([type_point, designator, lat, lon, id_point, country])
        del cursor
    elif name == 'rts':
        arcpy.CreateFeatureclass_management(out_path=work_path, out_name=result_shp, geometry_type='POINT', spatial_reference = sr)
        arcpy.AddField_management(result_shp, 'NAME_RUS','TEXT')
        arcpy.AddField_management(result_shp, 'NAME','TEXT')
        arcpy.AddField_management(result_shp, 'TYP','TEXT')
        arcpy.AddField_management(result_shp, 'FREQ','FLOAT')
        arcpy.AddField_management(result_shp, 'DESIGNATOR','TEXT')
        arcpy.AddField_management(result_shp, 'MAGVAR','DOUBLE')
        arcpy.AddField_management(result_shp, 'ID_','LONG')
        arcpy.AddField_management(result_shp, 'LATITUDE','TEXT')
        arcpy.AddField_management(result_shp, 'LONGITUDE','TEXT')
        arcpy.AddField_management(result_shp, 'CHANNEL','TEXT')
        arcpy.AddField_management(result_shp, 'Habs','DOUBLE')
        arcpy.AddField_management(result_shp, 'Rotate','DOUBLE', '6', '2', '', '','NULLABLE','NON_REQUIRED','')
        arcpy.AddField_management(result_shp, 'COUNTRY','TEXT')
        arcpy.AddField_management(result_shp, 'Notes','TEXT')
        arcpy.AddField_management(result_shp, 'ZZZ','LONG')

        with arcpy.da.InsertCursor(result_shp, ['NAME_RUS', 'NAME', 'TYP', 'FREQ', 'DESIGNATOR', 'MAGVAR', 'ID_', 
            'LATITUDE', 'LONGITUDE', 'CHANNEL', 'Habs', 'COUNTRY']) as cursor:
            for row in rows:
                name_rus = row[0]
                name = row[1]
                type = row[2]
                freq = float(row[3])
                designator = row[4]
                mag = float(row[5])
                id_point = long(row[6])
                lat = row[7]
                lon = row[8]
                channel = row[9]
                Habs = float(row[10])
                country = row[11]
                cursor.insertRow([name_rus, name, type, freq, designator, mag, id_point, lat, lon, channel, Habs, country])
        del cursor
    elif name == 'obstacles':
        arcpy.CreateFeatureclass_management(out_path=work_path, out_name=result_shp, geometry_type='POINT', spatial_reference = sr)
        arcpy.AddField_management(result_shp, 'NAME','TEXT')
        arcpy.AddField_management(result_shp, 'DESIGNATOR','TEXT')
        arcpy.AddField_management(result_shp, 'LENGTHM','DOUBLE')
        arcpy.AddField_management(result_shp, 'WIDTHM','DOUBLE')
        arcpy.AddField_management(result_shp, 'FRANGIBLE','TEXT')
        arcpy.AddField_management(result_shp, 'GEO_HEIGHT','DOUBLE')
        arcpy.AddField_management(result_shp, 'DATUM','TEXT')
        arcpy.AddField_management(result_shp, 'BRIGHT','TEXT')
        arcpy.AddField_management(result_shp, 'LIGHT_TYPE','TEXT')

        with arcpy.da.InsertCursor(result_shp, ['NAME', 'DESIGNATOR', 'LENGTHM', 'WIDTHM', 'FRANGIBLE', 'GEO_HEIGHT', 'DATUM', 
            'BRIGHT', 'LIGHT_TYPE']) as cursor:
            for row in rows:
                name = row[0]
                designator = row[1]
                length = float(row[2])
                width = float(row[3])
                frangible = row[4]
                height = float(row[5])
                datum = row[6]
                bright = row[7]
                light_type = row[8]
                cursor.insertRow([name, designator, length, width, frangible, height, datum, bright, light_type])
        del cursor
    del rows[:]
    print('End create shp-file')
