class bb : public Fijk
{
	private:
	string	_label;

    public:
	bb(u08 j, u08 k, string L) : Fijk(0xB, 0, j, k) { _label = L; }

	bool execute()
	{
	    if (PROC[me()].X(_j).i() - PROC[me()].X(_k).i() < 0) return true;
        else return false;
	}

	string mnemonic() const
	{
	    return "bb";
	}

	bool ops()
	{
	    process(new operations::cmp(_j, _k));
	    process(new operations::bb(_i));
	    return false;
	}
	
	void fixit()
	{
	    assert(PROC[me()].label2line.count(_label));
	    u32 targetline = PROC[me()].label2line[_label];
	    assert(PROC[me()].line2addr.count(targetline));
	    u32 targetaddr = PROC[me()].line2addr[targetline];
	    assert(PROC[me()].line2addr.count(_line));
	    u32 sourceaddr = PROC[me()].line2addr[_line];
	    assert(sourceaddr >= targetaddr);
	    _i = (sourceaddr/8) - (targetaddr/8); // Finally calculate and assert _i
	    assert(_i < 16);
	}
};
