/*  Copyright (C) 2010-2011  Jeremy Wootten
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * As a special exception, if you use inline functions from this file, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU Lesser General Public License.
 * 
 *  Author:
 * 	Jeremy Wootten <jeremwootten@gmail.com>
 */
 
 public class Gnonogram_region {

/** A region consists of a one dimensional array of cells, corresponding to a row or column of the puzzle
 Associated with this are:
	1) A list of block lengths (clues)
	2) A 'tag' boolean array for each cell with a flag for each block indicating whether it is still a possible owner and two extra flags - ' is completed' and ' can be empty'
	3) A 'completed blocks' boolean array with a flag for each block indicating whether it is completed.
	4) A status array, one per cell indicating the status of that cell as either UNKNOWN, FILLED (but not necessarily assigned to a completed block, EMPTY, or COMPLETED (assigned to a completed block).
**/
	private bool _is_column;
	public bool _in_error;
	public bool _completed;
	private bool[] _completed_blocks;
	private bool[,] _tags;
	private int [,] _ranges; //format: start,length,unfilled?,complete?
	private int _ncells;
	private int _nblocks;
	private int _block_total; //total cells to be filled
	private int _block_extent; //int.minimum span of blocks, including gaps of 1 cell.
	private int _index;
	private int _cycles;
	private int _pass;
	private int _unknown; 
	private int _filled; 
	private int _can_be_empty_ptr;
	private int _is_finished_ptr;
	private int[] _blocks;
	private My2DCellArray _grid;
	private CellState[] _status;
	private CellState[] _temp_status;
	private bool _debug;

//=========================================================================	
	public Gnonogram_region (My2DCellArray grid)
	{
		_grid=grid;
		_debug=false;
		_status=new CellState[Resource.MAXCOLSIZE];
		_temp_status=new CellState[Resource.MAXCOLSIZE];

// in order that size of class is determined and therefore an array of regions
// is possible, initialize all array variables to int.maximum possible size
// given size of grid. ??

		int maxblocks=Resource.MAXCOLSIZE/2+1;
		_ranges=new int[maxblocks,4];
		_blocks=new int[maxblocks];
		_completed_blocks=new bool[maxblocks];
		_tags=new bool[Resource.MAXCOLSIZE, maxblocks+2]; 	//two extra flags for "can be empty" and "is finished".
		
		_can_be_empty_ptr=maxblocks; //flag for cell that may be empty
		_is_finished_ptr=maxblocks+1; //flag for finished cell (filled or empty?)

	}
//=========================================================================	
	public void initialize(int index, bool iscolumn, int ncells, string blocks)
	{
		_index=index;
		_is_column=iscolumn;
		_ncells=ncells;
		_completed=false;
		_in_error=false;
		_block_total=0;
		_block_extent=0;
		_cycles=0;
		_pass=0;
		_unknown=99;
		_filled=99;
		
		_blocks=Utils.block_array_from_clue(blocks);
		_nblocks=_blocks.length;

		for (int i=0;i<_nblocks;i++)
		{
			_block_total=_block_total+_blocks[i];
			_completed_blocks[i]=false;
		}	
		_block_extent=_block_total+_nblocks-1; //last_block == number of gaps.

		for (int i=0;i<_ncells;i++)
		{
			for (int j=0; j<_nblocks; j++) _tags[i,j]=false;
			//Start with no possible owners and can be empty.
			_tags[i,_can_be_empty_ptr]=true;
			_tags[i,_is_finished_ptr]=false;
		}

		for (int i=0; i<_ncells;i++)
		{
			_status[i]=CellState.UNKNOWN;
			_temp_status[i]=CellState.UNKNOWN;
		}
	}

//======================================================================
	public bool solve(int pass)
	{
		/**cycles through ploys until no further changes can be made
		ignore single cell regions for testing purposes ...
		* */
		if (_completed||_ncells==1) return false; 
		
		_pass=pass;
		bool made_changes=false;
		bool still_changing=false;
		get_status();
		still_changing=totals_changed(); //always true when _cycles==0
		while (still_changing && !_completed)
		{
				_cycles++;
				if (_cycles==1) initial_fix();
				else
				{
					full_fix();
					tags_to_status();
				}
				
				if (_in_error) break;
				
				still_changing=totals_changed(); //always true when _cycles==1
				
				if (still_changing)
				{
					made_changes=true;
					_completed=(count_cell_state(CellState.UNKNOWN)==0);
				}
		}

		if (made_changes)
			{
				put_status();
				//truncate();  todo
			}

		return made_changes;
	}
//======================================================================
	private void initial_fix()
	{
		if (_blocks[0]==0)
		{
			_completed_blocks[0]=true;
			_completed=true;
		}
		else
		{
			int freedom=_ncells-_block_extent;
			if (freedom==0) _completed=true;
			
			int start=0;
			int length=0;
			
			for (int i=0; i<_nblocks; i++)
			{
				length=_blocks[i]+freedom;
				
				for (int j=start; j<start+length; j++) _tags[j,i]=true;

				start=start+_blocks[i]+1; //leave a gap between blocks
			}
		}
		tags_to_status();
	}
//======================================================================
	private void full_fix()
	{
		status_to_tags();
		if (do_edge(1)||_in_error) return;
		tags_to_status();

		if (do_edge(-1)||_in_error) return;
		tags_to_status();

		if (fill_gaps()||_in_error) return;
		tags_to_status();

		if (possibilities_audit()||_in_error) return;
		tags_to_status();

		if (filled_subregion_audit()||_in_error) return;
		tags_to_status();

		if (free_cell_audit()||_in_error) return;
		tags_to_status();

		if (only_possibility()||_in_error) return;
		tags_to_status();

		if (available_range_audit()||_in_error) return;
	}
//======================================================================
	private bool fill_gaps()
	{	// Find unknown gap between filled cells and complete accordingly.
		// Find an owned cell followed by an unknown gap
		// Find next filled cell - if same owner complete between 

		bool changed=false;
		
		for (int idx=0; idx<_ncells-1; idx++)
		{			
			if (_status[idx]!=CellState.FILLED) continue;
			if (_status[idx+1]!=CellState.UNKNOWN) continue;
			if (!one_owner(idx)) continue;
			
			idx++;
			int cell1=idx-1; //start of block
			while (idx<_ncells-1 && _status[idx]==CellState.UNKNOWN) idx++;
			
			if (_status[idx]!=CellState.FILLED) continue;
			
			int owner;
			if (same_owner(cell1,idx, out owner))
			{
				set_range_owner(owner,cell1,idx-cell1+1);
				changed=true;
			}
		}
		return changed;
	}
//======================================================================
	private bool possibilities_audit()
	{	//find a unique possible range for block if there is one.
		//eliminates ranges that are too small

		bool changed=false;
		int start=0;int length; int count=0;
		
		for (int i=0;i<_nblocks;i++)
		{			
			if (_completed_blocks[i]) continue; //skip completed block
			
			length=0;
			count=0;
			for (int idx=0;idx<_ncells;idx++)
			{				
				if (count>1) break;
				if (!_tags[idx,i]||_tags[idx,_is_finished_ptr]) continue;
				
				int l=count_next_owner(i,idx);
				int s=idx;
				
				if (l<_blocks[i])
				{//cant be here
					remove_block_from_range(i,s,l);
				}
				else
				{
					length=l;
					start=s;
					count++;
				}
				idx+=l;
			}
			
			if (count!=1) continue; //no usable range found
			else {//at least some cells can be assigned
				changed=fix_block_in_range(i,start,length)||changed;
			}
		}
		return changed;
	}
//======================================================================
	private bool filled_subregion_audit() {
//find a range of filled cells not completed and see if can be associated
// with a unique block.
		bool changed=false;
		int idx=0;
		int length;
		while (idx<_ncells)
		{//find a filled sub-region
		
			if (skip_while_not_status(CellState.FILLED,ref idx))
			{
				//idx points to first filled cell or returns false
				if (_tags[idx,_is_finished_ptr]) continue;//ignore if completed already
				
				length=count_next_state(CellState.FILLED, idx);//idx not changed

				int largest=find_largest_possible_in_cell(idx);
				
				if (largest==length)
				{//there is **at least one** largest block that fits exactly 
					assign_and_cap_range(idx,length);
					changed=true;
				}
				else
				{//remove blocks that are smaller than length and one cell either side
				
					for(int i=idx-1;i<=idx+length;i++)
					{						
						if (i<0||i>_ncells-1) continue;
						
						for (int bl=0;bl<_nblocks;bl++)
						{							
							if (_tags[i,bl] && _blocks[bl]<length) _tags[i,bl]=false;
						}
					}
				} 
				idx+=length;//move past block
			}
			else break;
		}
		return changed;	
	}
//=========================================================================	
	private void assign_and_cap_range(int start, int length)
	{	//make list of possible blocks with right length in max_blocks[]
		//record which is first and which last (in order).
		int count=0;
		int[] max_blocks=new int[_nblocks];
		int first=_nblocks;
		int last=0;
		
		for (int i=0;i<_nblocks;i++)
		{			
			if (_completed_blocks[i]) continue;
			if (_blocks[i]!=length) continue;
			if (!_tags[start,i]) continue;
			
			max_blocks[count]=i;
			count++;
			
			if (i<first) first=i;
			if (i>last) last=i;
		}
		
		if (count==1)
		{//unique owner
			set_block_complete_and_cap(max_blocks[0],start);
		}
		else
		{//ambiguous owner
			//delete out of sequence blocks before end of range
			for (int i=last;i<_nblocks;i++)
			{
				remove_block_from_cell_to_end(i,start+length-1,-1);
			}		
			//delete out of sequence blocks after start of range
			for (int i=0;i<=first;i++)
			{
				remove_block_from_cell_to_end(i,start,1);
			}
			//for each possible mark as possible owner of subregion (not exclusive)
			for (int i=0;i<count;i++)
			{
				set_range_owner(max_blocks[i],start,length,false);
			}
			//remove as possible owner blocks between first and last that are wrong length
			for (int i=first+1;i<last;i++)
			{
				if (_blocks[i]==length) continue;
				remove_block_from_range(i,start,length,1);
			}
			// cap range
			if (start>0) set_cell_empty(start-1);
			if (start+length<_ncells) set_cell_empty(start+length);
		}
	}	
//======================================================================
	private bool only_possibility()
	{ //find an unfinished cell with only one possibility

		bool changed=false;
		int owner;
		int length;
		int start;
		
		for (int i=0;i<_ncells;i++)
		{			
			if (_tags[i,_is_finished_ptr]) continue;
			
			if (_status[i]==CellState.FILLED && one_owner(i))
			{
				owner=0; //find the owner
				
				for (owner=0;owner<_nblocks;owner++)
				{					
					if (_tags[i,owner]) break;
				}
				
				length=_blocks[owner];
				start=i-length;
				if (start>=0) remove_block_from_cell_to_end(owner,start,-1);
				
				start=i+length;
				if (start<_ncells) remove_block_from_cell_to_end(owner,start,+1);					
			}
		}
		return changed;
	}

//======================================================================
	private bool free_cell_audit()
	{ 
		bool changed=false;
		int free_cells=count_cell_state(CellState.UNKNOWN);
		
		if (free_cells==0) return false;
		
		int filled_cells=count_cell_state(CellState.FILLED);
		int completed_cells=count_cell_state(CellState.COMPLETED);
		int to_locate=_block_total-filled_cells-completed_cells;
		
		if (free_cells==to_locate)
		{//free_cells>0
			for (int i=0;i<_ncells;i++)
			{
				if (_status[i]==CellState.UNKNOWN) set_cell_complete(i);
			}
			
			for (int i=0;i<_nblocks;i++) _completed_blocks[i]=true;
			
			changed=true;
		}
		else if (to_locate==0)
		{
			for (int i=0;i<_ncells;i++)
			{
				if (_status[i]==CellState.UNKNOWN) set_cell_empty(i);
			}
			changed=true;
		}
	
		return changed;
	}

//======================================================================
	private bool do_edge(int direction)
	{
		//1=forward -1=backward
		int idx; //pointer to current cell
		int blocknum; //current block
		int blength; // length of current block
		int limit; //first out of range value of idx depending on direction
		bool changed=false; //tags changed?
		bool dir=(direction>0);
		
		if (dir)
		{
			idx=0;
			blocknum=0;
			limit=_ncells;
		}
		else
		{
			idx=_ncells-1;
			blocknum=_nblocks-1;
			limit=-1;
		}
		
		if (!find_edge(ref idx,ref blocknum,limit,direction))
		{
			return false;
		}
		
		blength=_blocks[blocknum];
		
		if (_status[idx]==CellState.FILLED)
		{ //start of unassigned filled block
				set_block_complete_and_cap(blocknum,idx,direction);
				changed=true;
		}
		else
		{// see if filled cell in range of first block and complete after that
			int edge_start=idx;
			int fill_start=-1; 
			int blocklimit=(dir? idx+blength : idx-blength);
			
			if (skip_while_not_status(CellState.FILLED,ref idx,blocklimit,direction))
			{
				fill_start=idx;
				
				while (idx!=blocklimit)
				{
					if (_status[idx]==CellState.UNKNOWN)
					{
						set_cell_owner(idx,blocknum);
						changed=true;
					}
					
					if (dir) idx++;
					else idx--;
				} 
				//idx now points to cell after earliest possible end of block
				// if this is a filled cell then first cell in range must be empty
				// continue until an unfilled cell found setting cells at beginning of 
				//range empty
				while (idx!=blocklimit && _status[idx]==CellState.FILLED)
				{
					set_cell_owner(idx,blocknum);
					set_cell_empty(edge_start);
					changed=true;

					if (dir) {idx++; edge_start++;}
					else {idx--; edge_start--;}
				}
				//if a fillable cell was found then fill_start>0
				if (fill_start>0)
				{//delete block  than block length from where filling started
					idx= dir ? fill_start+blength : fill_start-blength;
					
					if (idx>=0 && idx<_ncells) remove_block_from_cell_to_end(blocknum,idx,direction);
				}
			}
		}
		return changed;
	}
//=========================================================================
	private bool find_edge(ref int idx,ref int blocknum, int limit, int direction)
	{
		bool dir=(direction>0);
		bool found=false;
		
		for (int i=idx; (dir ? i<limit : i>limit); (dir ? i++ : i--))
		{			
			if (_status[i]==CellState.EMPTY) continue;
			
			if (_tags[i,_is_finished_ptr])
			{//skip to end of finished block
				i = (dir ? i+_blocks[blocknum]-1 : i-_blocks[blocknum]+1);
				if (dir) blocknum++;
				else blocknum--;
				
				continue;
			}
			
			idx=i;
			found=true;
			break;
		}
		
		return found;
	}
//======================================================================
	private bool available_range_audit()
	{
		int start;
		int length;
		int filled;
		int unknown;
		int ranges;
		int nblocks;
		bool changed=false;
		
		ranges=count_available_ranges();

		for (int i=0;i<ranges;i++)
		{
			start=_ranges[i,0];
			length=_ranges[i,1];
			filled=_ranges[i,2];
			unknown=_ranges[i,3];
		}
		
		nblocks=blocks_available();
		if (nblocks!=ranges || nblocks<2) return false;
		
		int[] blocks=new int[nblocks];
		int bl=0;
		
		for (int i=0;i<_nblocks;i++)
		{
			if (!_completed_blocks[i])
			{
				blocks[bl]=i;
				bl++;
			}
		}
		//can more than one block fit? if not fix in range
		bool unique=true;
		for (int r=0; r<ranges; r++)
		{	
			if ((r<ranges-1) &&
				(_ranges[r,1]>=_blocks[blocks[r]]+_blocks[blocks[r+1]]+1)||
				(r>0) &&
				(_ranges[r,1]>=_blocks[blocks[r]]+_blocks[blocks[r-1]]+1)
				) {
			//this range must contain first block abort
				unique=false;
				break;
			}
		}
		
		if (unique)
		{	
			for (int r=0; r<ranges; r++) {
				fix_block_in_range(blocks[r],_ranges[r,0],_ranges[r,1]);
				changed=true;
			}
		}

		return changed;
	}
//======================================================================
	private bool skip_while_not_status(CellState cs, ref int idx, int limit=_ncells, int direction=1) {
// increments/decrements idx until cell of required state
// or end of range found.
//returns true if cell with status cs was found
		bool dir=(direction>0);
		bool found=false;
		
		for (int i=idx; (dir ? i<limit : i>limit); (dir ? i++ : i--))
		{	
			if (_status[i]==cs)
			{
				idx=i;
				found=true;
				break;
			}
		}	
		return found;	
	}
//======================================================================
	private int count_next_state(CellState cs, int idx)
	{
// count how may consecutive cells of state cs starting at given index idx?
		int count=0;
		if (idx>=0)
		{
			while ( _status[idx]==cs && idx<_ncells) {
				count++;
				idx++;
			}
		}
		else _in_error=true;
		return count;
	}
//======================================================================
	private int count_next_owner(int owner, int idx)
	{
// count how may consecutive cells with owner possible starting at given index idx?
		int count=0;
		if (idx>=0)
		{
			while ( _tags[idx,owner] &&
					!_tags[idx,_is_finished_ptr] &&
					 idx<_ncells) {
				count++;
				idx++;
			}
		}
		else _in_error=true;
		
		return count;
	}	
//======================================================================
	private int count_owners_and_empty(int cell) {
// how many possible owners?  Does include can be empty tag!
		int count=0;
		
		if (invalid_data(cell)) _in_error=true;
		else
		{	
			for (int j=0;j<_nblocks; j++) {

				if (_tags[cell,j]) count++;
			}
			
			if (_tags[cell,_can_be_empty_ptr]) count++;
		}
		return count;
	}	
//======================================================================
	private int count_cell_state(CellState cs) {
		//how many times does state cs occur in range.
		int count=0;
		for (int i=0;i<_ncells; i++)
		{
			if (_status[i]==cs) count++;
		}
		return count;
	}
//======================================================================
	private int count_available_ranges() {
// deterint.mine location of ranges of unknown or filled cells and store in _ranges[,]
// _ranges[ ,2] indicates contains filled, _ranges[ ,3] indicates contains unknown
		int range=0, start=0, length=0, idx=0;
		while (idx<_ncells)
		{
			length=0;
			start=idx;
			_ranges[range,0]=start;
			_ranges[range,2]=0;
			_ranges[range,3]=0;
			
			while (_status[idx]!=CellState.EMPTY && idx<_ncells)
			{					
				if (!_tags[idx,_can_be_empty_ptr])
				{
					_ranges[range,2]++;//contains filled cell
				}
				else _ranges[range,3]++; //contains unknown cell
				
				idx++; length++;
			}
			
			if (length>0 && _ranges[range,3]!=0)
			{
				_ranges[range,1]=length;
				range++;
			}
			
			while (_status[idx]==CellState.EMPTY && idx<_ncells) idx++;
		}
		return range;
	}
//======================================================================
	private int blocks_available() {
	//count incomplete blocks left?
		int available=0;
		for (int i=0; i<_nblocks; i++)
		{	
			if (!_completed_blocks[i]) available++;
		}
 		return available;
	}
//=========================================================================	
	private bool same_owner(int cell1, int cell2, out int owner) {
//checks if both the same single possible owner.  
//return true if same owner
//if true, 'owner' is initialised
		int count=0;
		owner=0;
		
		if (cell1<0||cell1>=_ncells||cell2<0||cell2>=_ncells)
		{
			_in_error=true;
		}
		else
		{
			for (int i=0; i<_nblocks; i++)
			{	
				if ((_tags[cell1,i]!=_tags[cell2,i])|| count>1)
				{
					count=0;
					break;
				}
				else if (_tags[cell1,i])
				{
					count++;
					owner=i;
				}
			}
		}
		return count==1;
	}
//======================================================================
	private bool one_owner(int cell) {
// if only one possible owner (if not empty) then return true 
		int count=0;
		for (int i=0; i<_nblocks; i++)
		{	
			if (_tags[cell,i]) count++;
			if (count>1) break;
		}
		return count==1;
	}
//=======================================================================
	private bool fix_block_in_range(int block, int start, int length,bool exclusive=true) {
// block must be limited to range
		bool changed=false;
		
		if (invalid_data(start,block, length)) {
			_in_error=true;
		}
		else
		{
			int block_length=_blocks[block];
			int freedom = length-block_length;
			
			if (freedom<block_length)
			{
				if (freedom==0)
				{
					set_block_complete_and_cap(block,start);
					changed=true;
				}
				else set_range_owner(block,start+freedom,block_length-freedom,exclusive);
			}
		}
		return changed;
	}	
//======================================================================
	private int find_largest_possible_in_cell(int cell)
	{
// find the largest incomplete block possible for given cell
		int max_size=-1;
		for (int i=0;i<_nblocks;i++)
		{	
			if (_completed_blocks[i]) continue;// ignore complete block
			if (!_tags[cell,i]) continue; // not possible
			if (_blocks[i]<=max_size) continue; // not largest
			max_size=_blocks[i]; //update largest
		}
		return max_size;
	}	
//======================================================================
	private void remove_block_from_cell_to_end(int block, int start,int direction=1)
	{
//remove block as possibility after/before start
//bi-directional forward=1 backward =-1
//if reverse direction then equivalent forward range is used
		int length=direction>0 ? _ncells-start : start+1;
		start=direction>0 ? start : 0;
		remove_block_from_range(block,start,length);
	}
//======================================================================
	private void remove_block_from_range(int block, int start, int length, int direction=1)
	{
//remove block as possibility in given range
//bi-directional forward=1 backward =-1
//if reverse direction then equivalent forward range is used
		if (direction<0) start=start-length+1;
		if (invalid_data(start,block, length))
		{
			_in_error=true;
		}
		else
		{
			for (int i=start; i<start+length; i++) _tags[i,block]=false;
		}
	}
//======================================================================
	private void set_block_complete_and_cap(int block, int start, int direction=1)
	{
		int length=_blocks[block];

		if (direction<0) start=start-length+1;
		if (invalid_data(start,block, length))
		{
			_in_error=true; return;	
		}
		
		if (_completed_blocks[block]==true && _tags[start,block]==false)
		{
			_in_error=true; return;
		}
		
		_completed_blocks[block]=true;
		set_range_owner(block,start,length);
		
		if (start>0) set_cell_empty(start-1);
		if (start+length<_ncells) set_cell_empty(start+length);
		
		for (int cell=start; cell<start+length; cell++) set_cell_complete(cell);
		//=======taking into account int.minimum distance between blocks.
		int l;
		if (block>1)
		{
			l=0;
			for (int bl=block-2;bl>=0;bl--)
			{
				l=l+_blocks[bl+1]+1;// length of exclusion zone for this block
				remove_block_from_range(bl,start-2,l,-1);
			}
		}
		if (block<_nblocks-2)
		{
			l=0;
			for (int bl=block+2;bl<=_nblocks-1;bl++)
			{
				l=l+_blocks[bl-1]+1;// length of exclusion zone for this block
				remove_block_from_range(bl,start+length+1,l,1);
			}
		}
	}

//======================================================================
	private void set_range_owner(int owner, int start, int length, bool exclusive=true)
	{	
		if (invalid_data(start,owner,length))
		{
			_in_error=true;
		}
		else
		{			
			int block_length=_blocks[owner];
			for (int cell=start; cell<start+length; cell++)
			{
				set_cell_owner(cell,owner,exclusive); //this checks owner valid
			}
			
			if (!exclusive) return;
			//remove block and out of sequence from regions out of reach if exclusive
			if (block_length<length)
			{
				_in_error=true; return;
			}
			
			if (start+length-block_length-1>=0)
			{				
				for (int bl=_nblocks-1;bl>=owner;bl--)
				{
					remove_block_from_cell_to_end(bl,start+length-block_length-1,-1);
				}
			}
			
			if (start+block_length<_ncells)
			{				
				for (int bl=0;bl<=owner;bl++)
				{
					remove_block_from_cell_to_end(bl,start+block_length);
				}
			}
		}		
	}
//======================================================================
	private void set_cell_owner(int cell, int owner, bool exclusive=true)
	{
		if (invalid_data(cell,owner))
		{
			_in_error=true;
		}
		else if (_status[cell]==CellState.EMPTY) {}// do nothing - not necessarily an error
		
		else if (_status[cell]==CellState.COMPLETED && _tags[cell,owner]==false)
		{
			_in_error=true;
		}
		else
		{
			if (exclusive)
			{
				_status[cell]=CellState.FILLED;
				_tags[cell,_can_be_empty_ptr]=false;
				for (int i=0; i<_nblocks; i++) _tags[cell,i]=false;
			}
			_tags[cell,owner]=true;
		}
	}
//======================================================================
	private void set_cell_empty(int cell)
	{
		if (invalid_data(cell))
		{
			_in_error=true;
		}
		else if (_tags[cell,_can_be_empty_ptr]==false)
		{
			_in_error=true;
		}
		
		else if (cell_filled(cell)) {
			_in_error=true;
		}
		else
		{
			for (int i=0; i<_nblocks; i++) _tags[cell,i]=false;
			
			_tags[cell,_can_be_empty_ptr]=true;
			_tags[cell,_is_finished_ptr]=true;
			_status[cell]=CellState.EMPTY;
		}
	}
//======================================================================
	private void set_cell_complete(int cell)
	{
		if (_status[cell]==CellState.EMPTY)
		{
			_in_error=true;
		}
		
		_tags[cell,_is_finished_ptr]=true;
		_tags[cell,_can_be_empty_ptr]=false;
		_status[cell]=CellState.COMPLETED;
	}
//======================================================================
	private bool invalid_data(int start, int block=0, int length=1)
	{
		return (start<0||start>=_ncells||length<1||start+length>_ncells||block<0||block>_nblocks); 
	}
//======================================================================
	private bool cell_filled(int cell)
	{
		return (_status[cell]==CellState.FILLED||_status[cell]==CellState.COMPLETED);
	}
//======================================================================
	private bool totals_changed()
	{
//has number of filled or unknown cells changed?
		if (_cycles==0) return true;
//forces fullfix even if initial fix does not make changes on first visit
// and cells have been set by intersecting ranges.

		bool changed=false;
		int unknown=count_cell_state(CellState.UNKNOWN);
		int filled=count_cell_state(CellState.FILLED);
		
		if (_unknown!=unknown || _filled!=filled)
		{
			changed=true;
			_unknown=unknown;
			_filled=filled;
			
			if (_filled>_block_total) _in_error=true;
		}
		
		return changed;
	}
//======================================================================
	private void get_status()
	{
//transfers cell statuses from grid to internal range status array
//		_grid.get_region(_index,_is_column, ref _temp_status);
		_grid.get_array(_index,_is_column, ref _temp_status);
		
		for (int i=0;i<_ncells; i++)
		{			
			switch (_temp_status[i])
			{				
				case CellState.UNKNOWN :
					break;
					
				case CellState.EMPTY :
				
					if (cell_filled(i))
					{
						_in_error=true;
					}
					else _status[i]=CellState.EMPTY;
					
					break;
					
				case CellState.FILLED :
					//dont overwrite COMPLETE status
					if (_status[i]!=CellState.COMPLETED) _status[i]=CellState.FILLED;
					break;
					
				default : break;
			}
		}
	}
//======================================================================
	private void put_status()
	{
		for (int i=0;i<_ncells; i++)
		{
			_temp_status[i]=(_status[i]==CellState.COMPLETED ? CellState.FILLED : _status[i]);
		}
		_grid.set_array(_index, _is_column, _temp_status);
	}
//======================================================================
	private void status_to_tags()
	{
		for(int i=0;i<_ncells;i++)
		{			
			switch (_status[i])
			{				
				case CellState.COMPLETED :
					_tags[i,_is_finished_ptr]=true;
					_tags[i,_can_be_empty_ptr]=false;
					break;
					
				case CellState.FILLED :
					_tags[i,_can_be_empty_ptr]=false; 
					break;
					
				case CellState.EMPTY :
				
					for (int j=0;j<_nblocks;j++) _tags[i,j]=false;
					
					_tags[i,_can_be_empty_ptr]=true;
					_tags[i,_is_finished_ptr]=true;
					break;
					
				default : break;
			}
		}
	}
//======================================================================
	private void tags_to_status()
	{
		for (int i=0;i<_ncells; i++)
		{
			// skip cells not unknown or with more than one possibility
			if (_status[i]!=CellState.UNKNOWN||count_owners_and_empty(i)>1) continue;
			//Either the 'can be empty' flag is set and there are no owners (ie cell is empty) or there is one owner.
			if (_tags[i,_can_be_empty_ptr]) _status[i]=CellState.EMPTY;
			else _status[i]=CellState.FILLED;
		}
	}
}
