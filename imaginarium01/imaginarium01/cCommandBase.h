/*
 * cCommandBase.h
 *
 *  Created on: 14. 2. 2017
 *      Author: GFreeman
 */

#ifndef CCOMMANDBASE_H_
#define CCOMMANDBASE_H_

class cCommandBase {
public:
	virtual ~cCommandBase(){};
	virtual void execute(void * arg_argument)=0;
};

#endif /* CCOMMANDBASE_H_ */
