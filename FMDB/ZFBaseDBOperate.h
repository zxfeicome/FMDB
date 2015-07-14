//
//  ZFBaseDBOperate.h
//  FMDB
//
//  Created by lx on 15/6/16.
//  Copyright (c) 2015年 huagu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDB.h"

#define kTableName @"ZFTable"

typedef enum {
    TableNameOne,
    TableNameTwo
}TableNameStyle;

@interface ZFBaseDBOperate : NSObject

@property (retain,nonatomic) FMDatabaseQueue *bindingQueue;

@property (retain,nonatomic) NSMutableDictionary *propertys;
@property (retain,nonatomic) NSMutableArray *columeNames;//列名
@property (retain,nonatomic) NSMutableArray *columeTypes;//列类型
@property (nonatomic,assign) TableNameStyle style;
#pragma mark - Init
/**
 *  初始化 这一步会创建表,queueStr是数据库名字
 */

-(instancetype)initWithDBQueue:(TableNameStyle)queueStr withArray:(NSDictionary *)dataDic;

/**
 *  返回表名 所有的DBOperate都必须重载此方法
 */
+(const NSString *)getTableName;
/**
 *  返回绑定的 Model Class 都必须重载此方法
 */
+(Class)getBindingModelClass;
/**
 *  清除创建表的历史记录
 */
+(void)clearCreateHistory;
/**
 *  给SQL语句增加列
 */
-(void)addColume:(NSString *)name type:(NSString *)type;
-(void)addcolumePrimary:(NSString *)name type:(NSString *)type;
/**
 *  返回create table parameter 语句
 */
-(NSString *)appendTableSql;
/**
 *  把oc/c类型转换为sqlite类型
    char/short/int/long     -->INTEGER
    long long               -->BIGINT
    float/double            -->REAL
    NSData/UIImage          -->BLOB
    其他                     -->TEXT
 */
+(NSString *)toDBType:(NSString *)type;
#pragma mark - create
//创建表
-(void)createTable;
#pragma mark - search
/**
 *  返回所有的数据
 */

-(void)searchAll:(void(^)(NSArray *))callBack;
/**
 *  返回特定where的所有数据
 */

-(void)searchAllWhere:(NSString *)where callback:(void(^)(NSArray *))block;
#pragma mark Search Page
/**
 *  默认返回 SEARCH_COUNT条数据
    pageNum 返回页数
 */
-(void)searchAllPageNum:(int)pageNum callback:(void(^)(NSArray *))block;
/**
 *默认返回SEARCH_COUNT 条数据
 orderBy 条件
 */
-(void)searchOrderBy:(NSString *)orderBy pageNum:(int)pageNum callback:(void(^)(NSArray *))block;
/**
 *  默认返回SEARCH_COUNT条数据
 *
 *  @param where   where条件，自定义
 *  @param orderBy 条件，按时间排序
 *  @param pageNum 页数。首页为0
 *  @param block   返回结果，对应的models
 */
-(void)searchWhere:(NSString *)where orderBy:(NSString *)orderBy pageNum:(int)pageNum callback:(void(^)(NSArray *))block;
#pragma mark Search key-value模式传入
/**
 *  返回SEARCH_COUNT条数据
 *
 *  @param whereDic where字典条件,例:@{@"name":@"Jay", @"age":@18}
 *  @param pageNum  第几页(0是首页)
 *  @param block    返回结果,对应的models
 */
- (void)searchWhereDic:(NSDictionary *)whereDic pageNum:(int)pageNum callback:(void(^)(NSArray*))block;
/**
 *  返回SEARCH_COUNT条数据
 *
 *  @param whereDic where字典条件,例:@{@"name":@"Jay", @"age":@18}
 *  @param orderBy  例:time DESC(按time排序)
 *  @param pageNum  第几页(0是首页)
 *  @param block    返回结果,对应的models
 */
- (void)searchWhereDic:(NSDictionary *)whereDic orderBy:(NSString *)orderBy pageNum:(int)pageNum callback:(void (^)(NSArray *))block;
#pragma mark - Insert

/**
 *  把model直接插入到数据库
 *
 *  @param model model
 *  @param block block
 */
//- (void)insertToDB:(NSObject<QMBaseDBModelDelegate> *)model callback:(void(^)(BOOL))block;
//
///**
// *  把model插入到数据库,如果存在(用primaryKey来判断),就更新(通过rowid或者primarykey来更新)
// *
// *  @param model model
// *  @param block block
// */
//- (void)insertToDBNotExistsOrUpdate:(NSObject<QMBaseDBModelDelegate> *)model callback:(void (^)(BOOL))block;


@end
