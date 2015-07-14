//
//  ZFBaseDBOperate.m
//  FMDB
//
//  Created by lx on 15/6/16.
//  Copyright (c) 2015年 huagu. All rights reserved.
//

#import "ZFBaseDBOperate.h"

#define QM_SQL_TEXT @"TEXT"
#define QM_SQL_INTEGER @"INTEGER"
#define QM_SQL_BIGINT @"BIGINT"
#define QM_SQL_FLOAT @"DECIMAL"    //DECIMAL/FLOAT/REAL
#define QM_SQL_BLOB @"BLOB"
#define QM_SQL_NULL @"NULL"
#define QM_SQL_INTEGER_PRIMARY_KEY @"INTEGER PRIMARY KEY"

/**
 *  查询数据库一页能查询到的个数
 */
#define DB_SEARCH_COUNT 10

@interface ZFBaseDBOperate(){
    NSMutableArray *values;
    NSArray *nameArr;
    NSArray *styleArr;
    NSArray *styles;
}

@end

static FMDatabase *_fmdb;

@implementation ZFBaseDBOperate
-(instancetype)initWithDBQueue:(TableNameStyle)queueStr withArray:(NSDictionary *)dataDic{
    self = [super init];
    if (self) {
        if (queueStr == TableNameOne) {
            values = [[NSMutableArray alloc] init];
            NSString *fileName = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.sqlite",kTableName]];
            _fmdb = [FMDatabase databaseWithPath:fileName];
            if (![_fmdb open]) {
                 NSLog(@"数据库打开失败");
           }else{
               [self getFMDBStr:dataDic withBlock:^(NSString *tableStr) {
                   NSString *fmStr = [NSString stringWithFormat:@"CREATE TABLE IF NOT EXISTS %@(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,%@)",kTableName,tableStr];
                   [_fmdb executeUpdate:fmStr];
               }];
               
            }
        }
        
    }
    return self;
}
//isHave代表是否有主键，主键在第一位
-(void)getFMDBStr:(NSDictionary *)dataDic withBlock:(void (^)(NSString *tableStr))block
{
    nameArr = [dataDic allKeys];
    styleArr = [dataDic allValues];
    
    styles = [self valueType:styleArr];
    NSMutableString *tableSql = [NSMutableString string];
    
    for (int i=0; i<styles.count; i++) {
        
        [tableSql appendFormat:@"%@ %@",nameArr[i],styles[i]];
        
        if (i + 1 != styles.count) {
            [tableSql appendString:@","];
        }
    }
    if (block) {
        block(tableSql);
    }
    
    
}

-(void)addcolumePrimary:(NSString *)name type:(NSString *)type{
    
}


//把数据类型转换成数据库的类型
-(NSString *)toDBType:(NSString *)type{
    if ([type isEqualToString:@"char"]||
        [type isEqualToString:@"short"]||
        [type isEqualToString:@"int"]||
        [type isEqualToString:@"long"]) {
        return QM_SQL_INTEGER;
    }else if ([type isEqualToString:@"float"]||
              [type isEqualToString:@"double"]){
        return QM_SQL_FLOAT;
    }else if ([type isEqualToString:@"long long"]){
        return QM_SQL_BIGINT;
    }else if ([type isEqualToString:@"NSData"]||
              [type isEqualToString:@"UIImage"]){
        return QM_SQL_BLOB;
    }
    return QM_SQL_TEXT;
}
-(NSArray *)valueType:(NSArray *)valueArr{

    [valueArr enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        NSString *str = NSStringFromClass([obj class]);
        NSString *classStr = [self toDBType:str];
        if (classStr.length > 0) {
            [values addObject:classStr];
        }
    }];
    
    return values;
    
}



@end
