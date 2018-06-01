//
//  NSObject+Log.m
//
//  Created by Stas Ivanov on 27.10.15.
//  Copyright © 2015 Stas Ivanov. All rights reserved.
//


#import "NSObject+Log.h"


@implementation NSObject (ModelLog)


+ (void) logNSException: (NSException*) exception function: (const char[]) function line: (NSInteger) line
{
    if (NO == [exception isKindOfClass: [NSException class]])
    {
        return;
    }
    
    NSString* message = [NSString stringWithFormat: @"exception = %@\n stack %@", exception, [NSThread callStackSymbols]];
    
    [self logLevel: ModelLogLevelException className: @"" function: function line: line message: message];
}


+ (void) logNSError: (NSError*) error function: (const char[]) function line: (NSInteger) line
{
    if (NO == [error isKindOfClass: [NSError class]])
    {
        return;
    }
    
    NSString* message = [NSString stringWithFormat: @"error = %@", error];
    
    [self logLevel: ModelLogLevelError className: @"" function: function line: line message: message];
}


+ (void) logLevel: (ModelLogLevel) logLevel className: (NSString*) className function: (const char[]) function line: (NSInteger) line message: (NSString*) message;
{
    @try
    {
        NSMutableString* logString = [NSMutableString new];
        
        [logString appendString: [self descriptionForLogLevel: logLevel]];
        [logString appendFormat: @" %@ | %i | %s | [Line %@]", className, [NSThread isMainThread], function, @(line)];
        
        if (message)
        {
            [logString appendFormat: @"\n%@", message];
        }
        
        [logString appendString: @"\n---------------\n"];
        
#ifdef USE_NSLOG
        NSLog(@"%@", logString);
#else
        printf("%s", [logString UTF8String]);
#endif
    }
    @catch (NSException *exception)
    {
        NSLog(@"\n\nLog exception = %@\n\n", exception);
    }
}


// http://apps.timwhitlock.info/emoji/tables/unicode

+ (NSString*) descriptionForLogLevel: (ModelLogLevel) logLevel
{
    NSString* description = @"";
    
    switch (logLevel)
    {
        case ModelLogLevelMethodStarted:
            description = @"\xF0\x9F\x94\x9B [Method started]";
            break;
            
        case ModelLogLevelDebug:
            description = @"\xF0\x9F\x94\xA8 [Debug]";
            break;
            
        case ModelLogLevelError:
            description = @"\xF0\x9F\x9A\xAB [Error]";
            break;
            
        case ModelLogLevelException:
            description = @"\xF0\x9F\x9A\xAB  [Exception]";
            break;
            
        case ModelLogLevelNetwork:
            description = @"\xF0\x9F\x93\xA1 [Network]";
            break;
    }
    
    return description;
}


@end
