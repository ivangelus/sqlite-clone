describe 'database' do
    before do
        `rm -rf test.db`
    end

    def run_script(commands)
        row_output = nil
            IO.popen("./db test.db", "r+") do |pipe|
            commands.each do |command|
                pipe.puts command
            end

            pipe.close_write

            # Read entire output
            row_output = pipe.gets(nil)
        end
        row_output.split("\n")
    end

    it 'inserts and retrieves a row' do
        result = run_script([
            "insert 1 ivan ivan@mail.com",
            "select",
            ".exit",
        ])
        expect(result).to match_array([
            "db > Executed.",
            "db > (1, ivan, ivan@mail.com)",
            "Executed.",
            "db > ",
        ])
    end

    it 'prints error message when table is full' do
        script = (1..1401).map do |i|
            "insert #{i} user#{i} mail#{i}@mail.com"
        end
        script << ".exit"
        result = run_script(script)
        expect(result[-2]).to eq('db > Error: Table full.')
    end

    it 'allows inserting strings that are maximum length' do
        long_username = "a"*32
        long_email = "a"*255
        script = [
            "insert 1 #{long_username} #{long_email}",
            "select",
            ".exit",
        ]
        result = run_script(script)
        expect(result).to match_array ([
            "db > Executed.",
            "db > (1, #{long_username}, #{long_email})",
            "Executed.",
            "db > ",
        ])
    end

    it 'prints error message if strings are long' do
        long_username = "a"*33
        long_email = "a"*256
        script = [
            "insert 1 #{long_username} #{long_email}",
            "select",
            ".exit",
        ]
        result = run_script(script)
        expect(result).to match_array([
            "db > String is too long.",
            "db > Executed.",
            "db > ",
        ])
    end

    it 'prints error message if ID is negative' do
        script = [
            "insert -1 user user@mail.com",
            "select",
            ".exit",
        ]

        result = run_script(script)
        expect(result).to match_array([
            "db > ID must be positive.",
            "db > Executed.",
            "db > ",
        ])
    end

    it 'allows inserting multiple rows' do
        script = [
            "insert 1 i i",
            "insert 2 b b",
            "select",
            ".exit",
        ]
        result = run_script(script)
        expect(result).to match_array ([
            "db > Executed.",
            "db > Executed.",
            "db > (1, i, i)",
            "(2, b, b)",
            "Executed.",
            "db > ",
        ])
    end

    it 'persists data' do
        result1 = run_script([
            "insert 1 i i",
            ".exit",
        ])
        expect(result1).to match_array([
            "db > Executed.",
            "db > ",
        ])
        result2 = run_script([
            "select",
            ".exit",
        ])
        expect(result2).to match_array([
            "db > (1, i, i)",
            "Executed.",
            "db > ",
        ])
    end

    it 'prints constants' do
        script = [
            ".constants",
            ".exit",
        ]
        result = run_script(script)
    
        expect(result).to match_array([
            "db > Constants:",
            "ROW_SIZE: 293",
            "COMMON_NODE_HEADER_SIZE: 6",
            "LEAF_NODE_HEADER_SIZE: 10",
            "LEAF_NODE_CELL_SIZE: 297",
            "LEAF_NODE_SPACE_FOR_CELLS: 4086",
            "LEAF_NODE_MAX_CELLS: 13",
            "db > ",
        ])
    end
    
    it 'allows printing out the structure of a one-node btree' do
      script = [3, 1, 2].map do |i|
        "insert #{i} user#{i} person#{i}@example.com"
      end
      script << ".btree"
      script << ".exit"
      result = run_script(script)
  
      expect(result).to match_array([
        "db > Executed.",
        "db > Executed.",
        "db > Executed.",
        "db > Tree:",
        "leaf (size 3)",
        "  - 0 : 3",
        "  - 1 : 1",
        "  - 2 : 2",
        "db > "
      ])
    end
end