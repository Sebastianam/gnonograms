/* Solver class for Gnonograms
 * Finds solution for a set of clues
 * Copyright (C) 2010-2011  Jeremy Wootten
 *
	This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Author:
 * 	Jeremy Wootten <jeremwootten@gmail.com>
 */

 public class Gnonogram_solver {

	private int _rows;
	private int _cols;
	private int _region_count;
	public My2DCellArray _grid;
	private Gnonogram_region[] _regions;
	private Cell _trial_cell;
	private int _rdir;
	private int _cdir;
	private int _rlim;
	private int _clim;
	private int _turn;
	private int _max_turns;
	private int _guesses=0;
	private int _counter=0;
	private bool _testing;
	private bool _debug;
	private bool _test_column;
	private int _test_idx;

	public signal void showsolvergrid();
	public signal void showprogress(int guesses);

	private const int GUESSES_BEFORE_ASK=50000;


	public Gnonogram_solver(bool testing=false, bool debug=false, bool test_column=false, int test_idx=-1)
	{
		_grid=new My2DCellArray(Resource.MAXSIZE, Resource.MAXSIZE);
		_regions=new Gnonogram_region[Resource.MAXSIZE+Resource.MAXSIZE];

		for (int i=0;i<_regions.length;i++) _regions[i]=new Gnonogram_region(_grid);

		//For development purposes only
		_testing=testing;
		_debug=debug;
		_test_column=test_column;
		_test_idx=test_idx;
		//
	}

	public void set_dimensions(int r, int c)
	{
		_rows=r;
		_cols=c;
	}

	public bool initialize(string[] row_clues, string[] col_clues, My2DCellArray? start_grid)
	{
		if (row_clues.length!=_rows || col_clues.length!=_cols)
		{
			stdout.printf("row/col size mismatch\n");
			return false;
		}

		if (start_grid==null) _grid.set_all(CellState.UNKNOWN);
		else {_grid.copy(start_grid);}

		//Create regions
		//Dont create regions of length 1
		_region_count=0;
		if(_cols>1) {
			for (int r=0; r<_rows; r++){
				_regions[r].initialize(r, false,_cols,row_clues[r]);
				_region_count++;
			}
		}
		if(_rows>1){
			for (int c=0; c<_cols; c++){
				_regions[c+_rows].initialize(c,true,_rows,col_clues[c]);
				_region_count++;
			}
		}
		_guesses=0; _counter=0;
		return valid();
	}

	public bool valid()
	{
		foreach (Gnonogram_region r in _regions)
			{ if (r._in_error) return false;}

		return true;
	}

	public string get_error()
	{
		for (int i=0; i<_region_count; i++)
		{
			if (_regions[i]._in_error) return _regions[i].message;
		}

		return "No error";
	}

	public int solve_it(bool debug, bool use_advanced=false, bool use_ultimate)
	{
		int simple_result=simple_solver(debug,true); //log errors
		if (simple_result==0 && use_advanced)
		{	if (!debug || Utils.show_confirm_dialog(_("Use advanced solver?")))
			{
				CellState[] grid_store= new CellState[_rows*_cols];
				int advanced_result=advanced_solver(grid_store, debug);
				if (advanced_result>0)
				{
					if(advanced_result==9999999 && use_ultimate)
					{
						return ultimate_solver(grid_store, debug);
					}
					else 	return advanced_result;
				}
			}
		}
		else
		{
			return simple_result;
		}
		return 0;
	}

	public bool get_hint()
	{
		//Solver must be initialised with current state of puzzle before calling.
		int		pass=1;
		while (pass<=30)
		{
			//cycle through regions until one of them is changed then returns
			//that region index.
			for (int i=0; i<_region_count; i++)
			{
				if (_regions[i]._completed) continue;
				if (_regions[i].solve(false,true)) //run solve algorithm in hint mode
				{
					//stdout.printf("Changed region %d\n",i);
					showsolvergrid();
					return true;
				}
				if (_regions[i]._in_error)
				{
					Utils.show_warning_dialog(_("A logical error has already been made - cannot hint"));
					return false;
				}
			}
			pass++;
		}
		if (pass>30)
		{
			if (solved())
			{
				Utils.show_info_dialog(_("Already solved"));
			}
			else
			{
				Utils.show_info_dialog(_("Simple solver could not find hint\n"));
			}
		}
		return false;
	}

	private int simple_solver(bool debug, bool log_error=false)
	{
		//stdout.printf(@"Simple solver  debug $debug  region count $_region_count\n");
		bool changed=true;
		int pass=1;
		while (changed && pass<30)
		{
			//keep cycling through regions while at least one of them is changing (up to 30 times)
			changed=false;
			for (int i=0; i<_region_count; i++)
			{
				if (_regions[i]._completed) continue;
				if (_regions[i].solve(debug)) changed=true;
				if (debug ||(log_error && _regions[i]._in_error))
				{
					if(_regions[i].message!="")stdout.printf("Region - %d: %s\n",i,_regions[i].message);
				}
				if (_regions[i]._in_error) return -1;
			}

			pass++;
			if (debug)
			{
				showsolvergrid();
				if (!Utils.show_confirm_dialog(@"Simple solver pass $pass ... continue?")) return 0;
			}
		}
		if (solved()) return pass;
		if (pass>30) Utils.show_warning_dialog("Simple solver - too many passes\n");
		return 0;
	}

	public bool solved()
	{
		for (int i=0; i<_region_count; i++)
		{
			if (!_regions[i]._completed) return false;
		}
		return true;
	}

	private int advanced_solver(CellState[] grid_store, bool debug)
	{
		// stdout.printf("Advanced solver\n");
		// single cell guesses, depth 1 (no recursion)
		// make a guess in each unknown cell in _turn
		// if leads to contradiction mark opposite to guess,
		// continue simple solve, if still no solution start again.
		// if does not lead to solution leave unknown and choose another cell
		int simple_result=0;
		int wraps=0;
		bool changed=false;
		int initial_maxturns=3; //stay near edges until no more changes
		CellState initial_cellstate=CellState.FILLED;

		_rdir=0; _cdir=1; _rlim=_rows; _clim=_cols;
		_turn=0; _max_turns=initial_maxturns;
		_trial_cell= {0,-1,initial_cellstate};

		this.save_position(grid_store);
		while (true)
		{
			increment_counter();
			make_guess();

			if (_trial_cell.col==-1) //run out of guesses
			{
				if (changed){}
				else if (_max_turns==initial_maxturns)
				{
					_max_turns=(int.min(_rows,_cols))/2+2; //ensure full coverage
				}
				else if(_trial_cell.state==initial_cellstate)
				{
					_trial_cell=_trial_cell.invert(); //start making opposite guesses
					_max_turns=initial_maxturns; wraps=0;
				}
				else break; //cant make progress

				_rdir=0; _cdir=1; _rlim=_rows; _clim=_cols; _turn=0;
				changed=false;
				wraps++;
				continue;
			}
			_grid.set_data_from_cell(_trial_cell);
			simple_result=simple_solver(false,false); //only debug advanced part, ignore errors

			if (simple_result>0) break; //solution found

			load_position(grid_store); //back track
			if (simple_result<0) //contradiction -  try opposite guess
			{
				_grid.set_data_from_cell(_trial_cell.invert()); //mark opposite to guess
				changed=true; //worth trying another cycle
				simple_result=simple_solver(false,false);//can we solve now?
				if (simple_result==0)
				{
					this.save_position(grid_store); //update grid store
					continue; //go back to start
				}
				else 	if (simple_result>0) break; // solution found
				else return -1; //starting point was invalid
			}
			else	continue; //guess again
		}
		//return vague measure of difficulty
		if (simple_result>0) return simple_result+_guesses;
		return 9999999;
	}

	private void save_position(CellState[] gs)
	{
		//store grid in linearised form.
		//stdout.printf("Save position\n");
		for(int r=0; r<_rows; r++)
		{	for(int c=0; c<_cols; c++)
			{
				gs[r*_cols+c]=_grid.get_data_from_rc(r,c);
			}
		}
		for (int i=0; i<_region_count; i++) _regions[i].save_state();
	}

	private void load_position(CellState[] gs)
	{
		//stdout.printf("Load position\n");
		for(int r=0; r<_rows; r++)
		{	for(int c=0; c<_cols; c++)
			{
				_grid.set_data_from_rc(r,c, gs[r*_cols+c]);
			}
		}
		for (int i=0; i<_region_count; i++) _regions[i].restore_state();
	}

	private void make_guess()
	{
		//Scan in spiral pattern from edges.  Critical cells most likely in this region
		int r=_trial_cell.row;
		int c=_trial_cell.col;

		while (true)
		{
			r+=_rdir; c+=_cdir; //only one changes at any one time
			if (_cdir==1 && c>=_clim) {c--;_cdir=0;_rdir=1;r++;} //across top - rh edge reached
			else if (_rdir==1 && r>=_rlim) {r--;_rdir=0;_cdir=-1;c--;} //down rh side - bottom reached
			else if (_cdir==-1 && c<_turn) {c++; _cdir=0;_rdir=-1;r--;} //back across bottom lh edge reached
			else if (_rdir==-1 && r<=_turn) {r++;_turn++;_rlim--;_clim--;_rdir=0;_cdir=1;} //up lh side - top edge reached
			if (_turn>_max_turns) {_trial_cell.row=0;_trial_cell.col=-1;break;} //stay near edge until no more changes
			if (_grid.get_data_from_rc(r,c)==CellState.UNKNOWN)
			{
				_trial_cell.row=r; _trial_cell.col=c;
				return;
			}
		}
		return;
	}

	public Cell get_cell(int r, int c)
	{
		return _grid.get_cell(r,c);
	}

	private int ultimate_solver(CellState[] grid_store, bool debug)
	{
		//stdout.printf("Ultimate solver\n");
		int perm_reg=-1, max_value=9999999, advanced_result=-99, simple_result=-99;
		int limit=GUESSES_BEFORE_ASK;

		load_position(grid_store); //return to last valid state
		for (int i=0; i<_region_count; i++) _regions[i].initial_state();
		simple_solver(false,true); //make sure region state correct

		showsolvergrid();
		if(!Utils.show_confirm_dialog(_("Start Ultimate solver?\n This can take a long time and may not work"))) return 9999999;

		CellState[] grid_store2 = new CellState[_rows*_cols];
		CellState[] guess={};

		while (true)
		{
			perm_reg=choose_permute_region(ref max_value);
			if (perm_reg<0) {stdout.printf("No perm region found\n");break;}

			int start;
			var p=_regions[perm_reg].get_permutor(out start);

			if (p==null|| p.valid==false){stdout.printf("No valid permutator generated\n");break;}

			bool is_column=_regions[perm_reg]._is_column;
			int idx=_regions[perm_reg]._index;

			//try advanced solver with every possible pattern in this range.

			for (int i=0; i<_region_count; i++) _regions[i].initial_state();
			save_position(grid_store2);

			p.initialise();
			while (p.next())
			{
				increment_counter();
				if (_guesses>limit)
				{
					if(Utils.show_confirm_dialog(_("This is taking a long time!")+"\n"+_("Keep trying?"))) limit+=GUESSES_BEFORE_ASK;
					else return 9999999;
				}
				guess=p.get();

				_grid.set_array(idx,is_column,guess,start);
				simple_result=simple_solver(false,false);

				if(simple_result==0)
				{
					advanced_result=advanced_solver(grid_store, debug);
					if (advanced_result>0 && advanced_result<9999999) return advanced_result; //solution found
				}
				else if (simple_result>0) return simple_result+_guesses; //unlikely!

				load_position(grid_store2); //back track
				for (int i=0; i<_region_count; i++) _regions[i].initial_state();
			}
			load_position(grid_store2); //back track

			for (int i=0; i<_region_count; i++) _regions[i].initial_state();
			simple_solver(false,false);
		}
		return 9999999;
	}

	private int choose_permute_region(ref int max_value)
	{
		int best_value=-1, current_value, perm_reg=-1,edg;
		for (int r=0;r<_region_count;r++)
		{
			current_value=_regions[r].value_as_permute_region();
			//weight towards edge regions
			if (current_value==0)continue;
			if (r<_rows)edg=int.min(r,_rows-1-r);
			else edg=int.min(r-_rows,_rows+_cols-r-1);
			edg+=1;
			current_value=current_value*100/edg;
			if (current_value>best_value&&current_value<max_value)
			{
				best_value=current_value;
				perm_reg=r;
			}
		}
		max_value=best_value;
		return perm_reg;
	}

	private void increment_counter()
	{
		//provide visual feedback
		_guesses++;	_counter++;
		if(_counter==100)
		{
			showprogress(_guesses); //signal to controller
			Utils.process_events();
			_counter=0;
		}
	}
}