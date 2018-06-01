//
//  NSObject+Log.h
//
//  Created by Stas Ivanov on 27.10.15.
//  Copyright © 2015 Stas Ivanov. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (Log)

typedef enum ModelLogLevel : NSUInteger {
    ModelLogLevelMethodStarted,
    ModelLogLevelDebug,
    ModelLogLevelError,
    ModelLogLevelNetwork,
    ModelLogLevelException
} ModelLogLevel;


#define USE_NSLOG


#define LOG_METHOD
#define LOG_DEBUG
#define LOG_NETWORK
#define LOG_ERROR
#define LOG_EXCEPTION


//-------------------- METHOD START
#ifdef LOG_METHOD
#   define LogMethod [NSObject logLevel: ModelLogLevelMethodStarted className: NSStringFromClass([self class]) function: __PRETTY_FUNCTION__ line: __LINE__ message: nil];
#else
#   define LogMethod
#endif

//-------------------- DEBUG
#ifdef LOG_DEBUG
#   define LogDebugMessage(format, ...) [NSObject logLevel: ModelLogLevelDebug className: NSStringFromClass([self class]) function: __PRETTY_FUNCTION__ line: __LINE__ message: [NSString stringWithFormat:format, ##__VA_ARGS__]];
#else
#   define LogDebugMessage(...)
#endif

//-------------------- NETWORK
#ifdef LOG_NETWORK
#   define LogNetworkMessage(format, ...) [NSObject logLevel: ModelLogLevelNetwork className: NSStringFromClass([self class]) function: __PRETTY_FUNCTION__ line: __LINE__ message: [NSString stringWithFormat:format, ##__VA_ARGS__]];
#else
#   define LogNetworkMessage(...)
#endif


//-------------------- ERROR
#ifdef LOG_ERROR
#   define LogError(e) [NSObject logNSError: e function: __PRETTY_FUNCTION__ line: __LINE__];
#else
#   define LogError(e)
#endif

#ifdef LOG_ERROR
#   define LogErrorMessage(format, ...) [NSObject logLevel: ModelLogLevelError className: NSStringFromClass([self class]) function: __PRETTY_FUNCTION__ line: __LINE__ message: [NSString stringWithFormat:format, ##__VA_ARGS__]];
#else
#   define LogErrorMessage(...)
#endif


//-------------------- EXCEPTION
#ifdef LOG_EXCEPTION
#   define LogException(e) [NSObject logNSException: e function: __PRETTY_FUNCTION__ line: __LINE__];
#else
#   define LogException(e)
#endif


+ (void) logLevel: (ModelLogLevel) logLevel className: (NSString*) className function: (const char[]) function line: (NSInteger) line message: (NSString*) message;

+ (void) logNSError: (NSError*) error function: (const char[]) function line: (NSInteger) line;

+ (void) logNSException: (NSException*) exception function: (const char[]) function line: (NSInteger) line;


@end
